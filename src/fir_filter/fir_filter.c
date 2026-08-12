#include <stddef.h>
#include <stdio.h>

#include "fir_filter.h"

/**
 * @brief Inicializa um filtro FIR associando coeficientes e histórico.
 *
 * Valida os ponteiros recebidos e o número de coeficientes, guarda
 * os coeficientes e a sua contagem na estrutura, e inicializa o
 * buffer circular interno (history) com tamanho igual a
 * num_coefficients — uma amostra de histórico por coeficiente,
 * necessário para calcular y[n] = sum(h[k] * x[n-k]) para k = 0..M-1.
 *
 * @param filter            Ponteiro para a estrutura FirFilter a inicializar.
 * @param coefficients       Coeficientes h[0..num_coefficients-1].
 * @param num_coefficients    Número de coeficientes do filtro (M).
 * @param history_storage    Memória externa para o buffer circular interno.
 */
void fir_init(FirFilter *filter, float *coefficients, size_t num_coefficients, float *history_storage) {
    if (filter == NULL || coefficients == NULL || history_storage == NULL || num_coefficients == 0) {
        fprintf(stderr, "Error: invalid arguments passed to fir_init\n");
        return;
    }

    filter->coefficients = coefficients;
    filter->num_coefficients = num_coefficients;

    rb_init(&filter->history, history_storage, num_coefficients);
}