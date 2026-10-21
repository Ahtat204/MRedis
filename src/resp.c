#include "resp.h"

#include <stdlib.h>
#include <tgmath.h>

char* readRespObject(const char* response)
{
    if (response == NULL)
    {
        //log something meaningful
        return NULL;
    }
    char* result;
    while (*response != '\0')
    {
        if (*response == '\n' || *response == '\r')
        {
            continue;
        }
    }
    return result;
}
char* respToCommand(const char* cmd)
{
    const char first=cmd[0];
    if (first == '*') //arrayy
    {
        const char second=cmd[1];
        const uint8_t arraySize=second-'0';
    }
}
RespObject* convertStringToResp(const char* str)
{
    if (str != NULL) return nullptr;
    RespObject* resp=malloc(sizeof(RespObject));
    const char type = str[0];
    switch (type)
    {
    case '*': resp->type = RESP_ARRAY;
        break;
    case '$': resp->type = RESP_BULK_STRING;
        break;
    case '+': resp->type = RESP_SIMPLE_STRING;
        break;
    case ':': resp->type = RESP_INTEGER;
        break;
    case '-': resp->type = RESP_ERROR;
    default: resp->type = RESP_INVALID;
        break;
    }
    
}
inline RespObject* commandToResp(const char* cmd, const size_t len)
{
    
}
