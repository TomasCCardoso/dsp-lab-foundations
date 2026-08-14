#include "ring_buffer.h"
#include <stdio.h>
#include <stdbool.h>

/**
 * @brief Inicializa o buffer circular.
 * 
 * Associa o buffer circular a um array de armazenamento fornecido e define o seu tamanho e dá reset à posição do head.
 * @param rb Ponteiro para a estrutura RingBuffer a ser inicializada.
 * @param storage Ponteiro para a memória usada para armazenar os dados do buffer circular.
 * @param size Capacidade total do vetor de armazenamento (quantas amostras cabem).
 */

 void rb_init(RingBuffer *rb, float *storage, size_t size) {

   if (rb == NULL || storage == NULL || size == 0) {
        fprintf(stderr, "Erro: ponteiro nulo ou tamanho inválido no rb_init.\n");
        return;
    }
    rb->storage = storage;
    rb->size = size;
    rb->head = 0;
    rb->count = 0;
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

 void rb_push(RingBuffer *rb, float sample)
{
    if (rb == NULL || rb->storage == NULL || rb->size == 0)
    {
        fprintf(stderr,
                "Error: invalid RingBuffer passed to rb_push().\n");
        return;
    }

    rb->storage[rb->head] = sample;
    rb->head = (rb->head + 1) % rb->size;
    if (rb->count < rb->size) {
        rb->count++;
    }
}
/**
 * @brief Devolve true se a mostra na posição i for válida, devolve false caso contrário.
 * O ponteiro out é usado para devolver o valor da amostra pedida.
 *
 * @param rb Ponteiro para a estrutura RingBuffer.
 * @param i  Posição relativa à amostra mais recente (0 = mais recente).
 * @param out Ponteiro para a variável onde armazenar o valor da amostra.
 * @return   true se a amostra for válida, false caso contrário.
 */

bool rb_get(const RingBuffer *rb, size_t i, float *out) {

    if (rb == NULL || rb->storage == NULL || rb->size == 0 || out == NULL)
    {
        fprintf(stderr,
                "Error: invalid RingBuffer passed to rb_get().\n");
        return false;
    } else if(i >= rb->count) {
        fprintf(stderr,
                "Error: requested index %zu is out of bounds (count = %zu).\n", i, rb->count);
        return false;
    }
    size_t index = (rb->head + rb->size - 1 - i) % rb->size;
    *out = rb->storage[index];
    return true;
}

