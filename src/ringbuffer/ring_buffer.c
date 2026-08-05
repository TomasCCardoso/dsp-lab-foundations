#include "ring_buffer.h"
#include <stdio.h>

/**
 * @brief Inicializa o buffer circular.
 * 
 * Associa o buffer circular a um array de armazenamento fornecido e define o seu tamanho e dá reset à posição do head.
 * @param rb Ponteiro para a estrutura RingBuffer a ser inicializada.
 * @param storage Ponteiro para a memória usada para armazenar os dados do buffer circular.
 * @param size Capacidade total do vetor de armazenamento (quantas amostras cabem).
 */

 void rb_init(RingBuffer *rb, float *storage, size_t size) {
    rb->storage = storage;
    rb->size = size;
    rb->head = 0;
}

/**
 * @brief Writes a new sample into the ring buffer.
 *
 * Stores the sample at the current write position and advances the
 * head index. When the end of the buffer is reached, the head wraps
 * around to the beginning, overwriting the oldest samples.
 *
 * @param rb Pointer to the RingBuffer structure.
 * @param sample Sample to be stored.
 */

 void rb_push(RingBuffer *rb, float sample) {
    rb->storage[rb->head] = sample;
    rb->head = (rb->head + 1) % rb->size;
 }
