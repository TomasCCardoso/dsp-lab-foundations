#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#include <stddef.h>
#include <stdbool.h>

typedef struct {
    float *storage;   // ponteiro para o array onde os dados vivem
    size_t size;       // capacidade total (quantas amostras cabem)
    size_t head;        // índice da próxima posição a escrever
    size_t count;       // número de amostras atualmente armazenadas
} RingBuffer;

void rb_init(RingBuffer *rb, float *storage, size_t size);
void rb_push(RingBuffer *rb, float sample);
bool rb_get(const RingBuffer *rb, size_t i, float *out);

#endif // RING_BUFFER_H

