//
// Created by ahtat204 on 10/1/26.
//

#ifndef MREDIS_RESP_H
#define MREDIS_RESP_H
#if __linux__
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    PARSER_STATE_READING_TYPE,
    PARSER_STATE_READING_LENGTH,
    PARSER_STATE_READING_DATA,
    PARSER_STATE_READING_CRLF
}Read_State;
struct RespObject; // Forward declaration

typedef enum {
    RESP_SIMPLE_STRING='+',
    RESP_ERROR='-',
    RESP_INTEGER=':',
    RESP_BULK_STRING='$',
    RESP_ARRAY='*',
    RESP_INVALID
} RespType;
typedef struct RespObject {
    RespType type;
    long long integer_value;    // For :integers
    char *string_value;        // For +, -, and $ strings
    int string_len;            // For $ strings (can be -1 for Null Bulk String)
    struct RespObject **array_elements; // For * arrays
    int array_len;             // For * arrays (can be -1 for Null Array)
} RespObject;
// this will read the resp serialized command , ex : $5\r\nAhmed\r\n"
char* encode_client_command(int argc, char **argv, size_t *out_len);
void free_resp_object(RespObject *obj);
RespObject* decode_resp(const char *src, size_t limit, size_t *bytes_read);
#endif//__linux
#endif //MREDIS_RESP_H



