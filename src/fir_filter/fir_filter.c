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