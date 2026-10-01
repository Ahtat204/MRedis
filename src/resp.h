//
// Created by ahtat204 on 10/1/26.
//

#ifndef MREDIS_RESP_H
#define MREDIS_RESP_H
#if __linux__
#include <stddef.h>
#include <stdint.h>

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
    union {
        char *str;             // For Simple String, Error, and Bulk String
        int64_t integer;       // For Integers
        struct {
            struct RespObject **elements;
            size_t count;
        } array;               // For Arrays
    } value;
    size_t len;                // Length for strings
} RespObject;

// this will read the resp serialized command , ex : $5\r\nAhmed\r\n"
char* respToCommand(const char* cmd);
char* readArray(const char* cmd);
int8_t readInt(const char* cmd);
char* readString(const char* cmd);
RespObject* commandToResp(const char* cmd,const size_t len); // this will convert to human-readable command ex: SET key value
#endif//__linux
#endif //MREDIS_RESP_H



