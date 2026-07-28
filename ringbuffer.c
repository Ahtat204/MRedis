#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#define RINGBUFFER_SIZE 1024

typedef struct 
{
    char buffer[RINGBUFFER_SIZE];
    char *read;
    char *write;
    size_t size;
}ringbuffer;

void init(ringbuffer *rb)
{
    rb->write = rb->read=&(rb->buffer[0]);
    rb->size = 0;
}
char readData(ringbuffer* rb)
{
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

