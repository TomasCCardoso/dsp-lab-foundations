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

   if (rb == NULL || storage == NULL || size == 0) {
        fprintf(stderr, "Erro: ponteiro nulo ou tamanho inválido no rb_init.\n");
        return;
    }
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
}
/**
 * @brief Devolve a i-ésima amostra mais recente do buffer circular.
 *
 * i = 0 devolve a amostra mais recente (última escrita), i = 1 a
 * segunda mais recente, e assim sucessivamente. A posição real no
 * array é calculada com aritmética modular, somando rb->size antes
 * de subtrair para evitar underflow em size_t (unsigned).
 *
 * @param rb Ponteiro para a estrutura RingBuffer.
 * @param i  Posição relativa à amostra mais recente (0 = mais recente).
 * @return   Valor da amostra pedida, ou 0.0f se os argumentos forem inválidos.
 */

float rb_get(RingBuffer *rb, size_t i) {

    if (rb == NULL || rb->storage == NULL || rb->size == 0)
    {
        fprintf(stderr,
                "Error: invalid RingBuffer passed to rb_push().\n");
        return 0.0f;
    }

    size_t index = (rb->head + rb->size - 1 - i) % rb->size;
    return rb->storage[index];
}
