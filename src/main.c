#include <stdio.h>
#include <stddef.h>

#include "ring_buffer/ring_buffer.h"
#include "fir_filter/fir_filter.h"

int main(void)
{
    float coefficients[3] = {1.0f/3.0f, 1.0f/3.0f, 1.0f/3.0f};
    float history_storage[3];

    FirFilter filter;
    fir_init(&filter, coefficients, 3, history_storage);

    float input[6] = {10.0f, 20.0f, 30.0f, 40.0f, 50.0f, 60.0f};

    for (size_t i = 0; i < 6; i++) {
        float y = fir_process(&filter, input[i]);
        printf("x[%zu] = %.2f  ->  y[%zu] = %.4f\n", i, input[i], i, y);
    }

    return 0;
}