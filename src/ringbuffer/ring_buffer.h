#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#include <stddef.h>


typedef struct {
    float *storage;   // ponteiro para o array onde os dados vivem
    size_t size;       // capacidade total (quantas amostras cabem)
    size_t head;        // índice da próxima posição a escrever
} RingBuffer;

void rb_init(RingBuffer *rb, float *storage, size_t size);
void rb_push(RingBuffer *rb, float sample);
float rb_get(RingBuffer *rb, size_t i);

#endif // RING_BUFFER_H

