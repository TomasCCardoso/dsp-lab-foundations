#include "fir_filter/fir_filter.h"

bool fir_filter_init(FirFilter *filter, const float *coefficients, size_t num_coefficients, float *history_storage,size_t history_size) {
    /*
     * Validate all input parameters before modifying the filter state.
     *
     * The history storage provided by the caller must have enough
     * capacity to store one sample for each filter coefficient.
     */
    if (filter == NULL ||  coefficients == NULL ||num_coefficients == 0 || history_storage == NULL || history_size < num_coefficients)
    {
        return false;
    }

    /*
     * Store a reference to the coefficient array.
     * The caller retains ownership of this memory, which must remain
     * valid and unchanged while the filter is in use.
     */
    filter->coefficients = coefficients;

    /* Store the number of filter taps. */
    filter->num_coefficients = num_coefficients;

    /*
     * Initialize the input history buffer.
     * Its logical capacity matches the number of filter coefficients,
     * while the caller may provide a larger storage array.
     */
    rb_init(&filter->history, history_storage, num_coefficients);

    return true;
}
/**
 * @brief Processa uma nova amostra através do filtro FIR.
 *
 * Armazena a nova amostra no buffer de histórico e calcula a saída
 * do filtro através da convolução entre os coeficientes e as amostras
 * de entrada disponíveis.
 *
 * A equação implementada é:
 *
 *     y[n] = sum(h[k] * x[n-k])
 *
 * Enquanto o histórico ainda não tiver num_coefficients amostras
 * reais (logo após a inicialização do filtro), os coeficientes cujas
 * amostras x[n-k] ainda não existem são simplesmente ignorados na
 * soma — não é feito zero-padding explícito, mas o resultado
 * numérico é equivalente a tratá-las como zero.
 *
 * @param filter Ponteiro para o filtro FIR.
 * @param input_sample Nova amostra de entrada x[n].
 * @return Amostra de saída y[n].
 */
float fir_filter_process(FirFilter *filter, float input_sample)
{
    float output_sample = 0.0f;

    /* Store the new input sample in the history buffer. */
    rb_push(&filter->history, input_sample);

    /* Compute the FIR convolution. */
    for (size_t i = 0; i < filter->num_coefficients; i++)
    {
        float history_sample;

        if (rb_get(&filter->history, i, &history_sample))
        {
            output_sample += filter->coefficients[i] * history_sample;
        }
    }

    return output_sample;
}