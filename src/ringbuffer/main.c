#include <stdio.h>
#include <stddef.h>

#include "ring_buffer.h"

int main(void)
{
    float storage[4];

    RingBuffer rb;

    rb_init(&rb, storage, 4);

    rb_push(&rb, 10.0f);
    rb_push(&rb, 20.0f);
    rb_push(&rb, 30.0f);
    rb_push(&rb, 40.0f);
    rb_push(&rb, 50.0f);

    printf("Head = %zu\n", rb.head);

    for (size_t i = 0; i < rb.size; i++)
    {
        printf("[%zu] = %.1f\n", i, rb.storage[i]);
    }

    return 0;
}