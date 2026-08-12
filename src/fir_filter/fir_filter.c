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
/**
 * @brief Processa uma amostra de entrada através do filtro FIR.
 *
 * Insere a nova amostra x_n no histórico circular (tornando-a a mais
 * recente) e calcula a saída y[n] como combinação linear das últimas
 * num_coefficients amostras, ponderadas pelos coeficientes do filtro:
 *
 *     y[n] = sum_{k=0}^{M-1} h[k] * x[n-k]
 *
 * onde rb_get(k) devolve x[n-k] diretamente, já que k=0 corresponde
 * à amostra mais recente inserida.
 *
 * @param filter   Ponteiro para a estrutura FirFilter, já inicializada.
 * @param x_n      Nova amostra de entrada, x[n].
 * @return         Amostra de saída y[n], ou 0.0f se os argumentos forem inválidos.
 */
float fir_process(FirFilter *filter, float x_n) {
    if (filter == NULL || filter->coefficients == NULL || filter->num_coefficients == 0) {
        fprintf(stderr, "Error: invalid arguments passed to fir_process\n");
        return 0.0f;
    }

    rb_push(&filter->history, x_n);

    float y_n = 0.0f;
    for (size_t i = 0; i < filter->num_coefficients; i++) {
        float x_n_k = rb_get(&filter->history, i);
        float h_k = filter->coefficients[i];
        y_n = y_n + h_k * x_n_k;
    }

    return y_n;
}