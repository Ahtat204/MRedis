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


