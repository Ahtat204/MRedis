#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include "ringbuffer.h"

#include <stdlib.h>


int8_t init(ringbuffer* rb)
{
    if (!rb) return RB_MEMORY_ERROR;
    rb->buffer = malloc(RINGBUFFER_SIZE * sizeof(char));
    rb->write = rb->read = &(rb->buffer[0]);
    rb->read = rb->write;
    rb->size = 0;
    return RB_SUCCESS;
}

char readData(ringbuffer* rb)
{
    if (!rb) return RB_MEMORY_ERROR;;
    if (rb->size == 0) return '\0';
    const char data = (rb->buffer[*(rb->read)]);
    *(rb->read) = *(rb->read + 1) % RINGBUFFER_SIZE;
    rb->size--;
    return data;
}

uint8_t writeData(ringbuffer* b, const char character)
{
    if (b->size == RINGBUFFER_SIZE)
    {
        fprintf(stderr, "Error: Allocation failed.\n");
        return 0;
    }
    b->buffer[*b->write] = character;
    *b->write = (*b->write + 1) % RINGBUFFER_SIZE;
    b->size++;
    return 1;
}

uint8_t freeBuffer(ringbuffer* b)
{
    if (!b) return RB_MEMORY_ERROR;
    free(b->buffer);
    return RB_SUCCESS;
}
