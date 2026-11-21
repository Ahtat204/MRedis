//
// Created by ahtat204 on 11/8/26.
//
#include <stdio.h>
#include <stdlib.h>

#ifndef MREDIS_UTILS_H
#define MREDIS_UTILS_H
static const char* find_crlf(const char *src, size_t limit) {
    for (size_t i = 0; i < limit - 1; i++) {
        if (src[i] == '\r' && src[i+1] == '\n') {
            return &src[i];
        }
    }
    return NULL;
}
// Helper: Parse a number line ending with \r\n
static const char* parse_long_long(const char *src, size_t limit, long long *out_val) {
    const char *crlf = find_crlf(src, limit);
    if (!crlf) return NULL;

    char tmp[32];
    size_t digits_len = crlf - src;
    if (digits_len >= sizeof(tmp)) return NULL;

    strncpy(tmp, src, digits_len);
    tmp[digits_len] = '\0';
    *out_val = atoll(tmp);

    return crlf + 2; // Move past \r\n
}
#endif //MREDIS_UTILS_H