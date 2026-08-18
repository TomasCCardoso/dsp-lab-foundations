#ifndef FIR_FILTER_H
#define FIR_FILTER_H

#include <stddef.h>
#include <stdbool.h>
#include "ring_buffer/ring_buffer.h"

typedef struct {
    const float *coefficients; // ponteiro para o array de coeficientes do filtro
    size_t num_coefficients; // número de coeficientes do filtro
    RingBuffer history; // buffer circular para armazenar as amostras de entrada anteriores
} FirFilter;

bool  fir_filter_init(FirFilter *filter, const float *coefficients, size_t num_coefficients, float *history_storage, size_t history_size);
float fir_filter_process(FirFilter *filter, float input_sample);

#endif // FIR_FILTER_H