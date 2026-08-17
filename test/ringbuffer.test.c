//
// Created by ahtat204 on 8/15/26.
#include <criterion/criterion.h>
#include"../src/ringbuffer.h"

Test(resp,ring_buffer)
{
    struct buffer* rb=malloc(sizeof(struct buffer));
    const int result=init(rb);
    
}