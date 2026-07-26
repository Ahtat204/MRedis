#include <stddef.h>
#include <stdint.h>

#define RINGBUFFER_SIZE 1024

typedef struct 
{
    char buffer[RINGBUFFER_SIZE];
    char *read;
    char *write;
}ringbuffer;

char readData(ringbuffer* ringbuffer)
{
    
}
char writeData(ringbuffer* ringbuffer,char character)
{
    *(ringbuffer->write)= character;
}

