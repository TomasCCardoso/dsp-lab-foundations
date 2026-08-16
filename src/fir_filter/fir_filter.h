#ifndef FIR_FILTER_H
#define FIR_FILTER_H

#include <stddef.h>
#include "ring_buffer/ring_buffer.h"

/**
 * @brief Estrutura de um filtro FIR (Finite Impulse Response).
 *
 * Guarda os coeficientes (taps) do filtro e um buffer circular
 * interno (history) com as últimas num_coefficients amostras de
 * entrada, usado para calcular a convolução em modo streaming
 * (amostra a amostra), evitando o custo de deslocar um array
 * manualmente a cada nova amostra.
 */
typedef struct {
    RingBuffer history;         ///< buffer circular com as últimas amostras de entrada
    float *coefficients;         ///< coeficientes h[0..num_coefficients-1]
    size_t num_coefficients;      ///< número de coeficientes do filtro (M)
} FirFilter;

/**
 * @brief Inicializa um filtro FIR.
 *
 * Associa o filtro a um conjunto de coeficientes fornecido
 * externamente, e inicializa o buffer circular interno que guarda
 * o histórico das últimas num_coefficients amostras de entrada.
 * A memória de history_storage deve ter capacidade para pelo menos
 * num_coefficients floats, e é fornecida pelo caller — o filtro
 * não aloca memória própria.
 *
 * @param filter            Ponteiro para a estrutura FirFilter a inicializar.
 * @param coefficients       Coeficientes h[0..num_coefficients-1].
 * @param num_coefficients    Número de coeficientes do filtro (M).
 * @param history_storage    Memória externa para o buffer circular interno,
 *                           com capacidade >= num_coefficients floats.
 */
void fir_init(FirFilter *filter, float *coefficients, size_t num_coefficients, float *history_storage);
/**
 * @brief Processa uma amostra de entrada e devolve a saída do filtro FIR.
 *
 * @param filter   Ponteiro para a estrutura FirFilter, já inicializada.
 * @param x_n      Nova amostra de entrada, x[n].
 * @return         Amostra de saída y[n].
 */
float fir_process(FirFilter *filter, float x_n);
#endif // FIR_FILTER_H