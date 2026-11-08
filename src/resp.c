#include "resp.h"

#include <stdio.h>
#include <stdlib.h>


void free_resp_object(RespObject *obj) {
    if (!obj) return;
    if (obj->string_value) free(obj->string_value);
    if (obj->array_elements) {
        for (int i = 0; i < obj->array_len; i++) {
            free_resp_object(obj->array_elements[i]);
        }
        free(obj->array_elements);
    }
    free(obj);
}
char* encode_client_command(int argc, char **argv, size_t *out_len) {
    // Determine the size required first
    size_t total_size = 64; // arbitrary initial buffer cushion
    for (int i = 0; i < argc; i++) {
        total_size += 32 + strlen(argv[i]); 
    }

    char *buf = malloc(total_size);
    if (!buf) return NULL;

    // Format the top-level array header (*<count>\r\n)
    int offset = sprintf(buf, "*%d\r\n", argc);

    // Append each argument as a bulk string ($<len>\r\n<arg>\r\n)
    for (int i = 0; i < argc; i++) {
        size_t len = strlen(argv[i]);
        offset += sprintf(buf + offset, "$%zu\r\n%s\r\n", len, argv[i]);
    }

    *out_len = offset;
    return buf;
}
RespObject* decode_resp(const char *src, size_t limit, size_t *bytes_read) {
    if (limit < 3) return NULL; // Minimal possible payload size is 3 bytes (e.g. :0\r\n)

    char prefix = src[0];
    const char *ptr = src + 1;
    size_t remaining = limit - 1;

    RespObject *obj = calloc(1, sizeof(RespObject));
    if (!obj) return NULL;

    switch (prefix) {
        case '+': // Simple String
        case '-': // Error
        {
            obj->type = (prefix == '+') ? RESP_SIMPLE_STRING : RESP_ERROR;
            const char *crlf = find_crlf(ptr, remaining);
            if (!crlf) goto error;

            size_t len = crlf - ptr;
            obj->string_value = malloc(len + 1);
            memcpy(obj->string_value, ptr, len);
            obj->string_value[len] = '\0';
            obj->string_len = (int)len;

            *bytes_read = (crlf + 2) - src;
            return obj;
        }
        case ':': // Integer
        {
            obj->type = RESP_INTEGER;
            const char *next = parse_long_long(ptr, remaining, &obj->integer_value);
            if (!next) goto error;

            *bytes_read = next - src;
            return obj;
        }
        case '$': // Bulk String
        {
            obj->type = RESP_BULK_STRING;
            long long bulk_len = 0;
            const char *next = parse_long_long(ptr, remaining, &bulk_len);
            if (!next) goto error;

            if (bulk_len == -1) { // Null Bulk String
                obj->string_value = NULL;
                obj->string_len = -1;
                *bytes_read = next - src;
                return obj;
            }

            remaining = limit - (next - src);
            if (remaining < (size_t)bulk_len + 2) goto error; // Ensure payload + \r\n exists

            obj->string_value = malloc(bulk_len + 1);
            memcpy(obj->string_value, next, bulk_len);
            obj->string_value[bulk_len] = '\0';
            obj->string_len = (int)bulk_len;

            if (next[bulk_len] != '\r' || next[bulk_len + 1] != '\n') goto error;

            *bytes_read = (next + bulk_len + 2) - src;
            return obj;
        }
        case '*': // Array
        {
            obj->type = RESP_ARRAY;
            long long count = 0;
            const char *next = parse_long_long(ptr, remaining, &count);
            if (!next) goto error;

            if (count == -1) { // Null Array
                obj->array_elements = NULL;
                obj->array_len = -1;
                *bytes_read = next - src;
                return obj;
            }

            obj->array_len = (int)count;
            if (count == 0) {
                obj->array_elements = NULL;
                *bytes_read = next - src;
                return obj;
            }

            obj->array_elements = calloc(count, sizeof(RespObject*));
            size_t total_consumed = next - src;

            for (int i = 0; i < count; i++) {
                size_t element_consumed = 0;
                obj->array_elements[i] = decode_resp(src + total_consumed, limit - total_consumed, &element_consumed);
                if (!obj->array_elements[i]) goto error;
                total_consumed += element_consumed;
            }

            *bytes_read = total_consumed;
            return obj;
        }
        default:
            goto error; // Unknown or unhandled RESP type prefix
    }

error:
    free_resp_object(obj);
    return NULL;
}
