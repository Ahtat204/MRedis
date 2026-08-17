//
// Created by ahtat204 on 8/15/26.
#include <criterion/criterion.h>
#include"../src/ringbuffer.h"

Test(resp,ring_buffer)
{
    struct buffer* rb=malloc(sizeof(struct buffer));
    const int result=init(rb);
    cr_expect_neq(rb, NULL,"the buffer struct must not be null");
    cr_expect_neq(rb->buffer,NULL,"the buffer array must not be null");
    free(rb);
    
}