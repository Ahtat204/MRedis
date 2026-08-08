#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include"ringbuffer.h"

typedef struct buffer
{
    char* buffer;
    char *read;
    char *write;
    size_t size;
}ringbuffer;

int init(ringbuffer *rb)
{
    if (!rb) return RB_MEMORY_ERROR;
    rb->write = rb->read=&(rb->buffer[0]);
    rb->size = 0;
    return RB_SUCCESS;
}
char readData(ringbuffer* rb)
{
    if (!rb) return RB_MEMORY_ERROR;;
    if (rb->size==0) return '\0';
    const char data=(rb->buffer[*(rb->read)]);
    *(rb->read)=*(rb->read+1)%RINGBUFFER_SIZE;
    rb->size--;
    return data;
}
uint8_t writeData(ringbuffer* b,const char character)
{
   if (b->size==RINGBUFFER_SIZE)
   {
       printf(stderr);
       return 0;
   }
    b->buffer[*b->write]=character;
    *b->write=(*b->write+1)%RINGBUFFER_SIZE;
    b->size++;
    return 1;
    
}

