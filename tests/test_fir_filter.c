#include "fir_filter/fir_filter.h"
#include <stdio.h>

void check(bool condition, const char *message) {
    if(condition) {
        printf("PASS: %s\n", message);
    } else {
        printf("FAIL: %s\n", message);
    }
}

void test_fir_filter_init(void) {
    FirFilter filter;
    const float *coefficients = (const float[]) {0.25f, 0.5f, 0.25f};
    size_t num_coefficients = 3;
    float history_storage[3];
    size_t history_size = 3;
    bool result = fir_filter_init(&filter, coefficients, num_coefficients, history_storage, history_size);
    check(result, "FIR filter initialization");
    check(filter.coefficients == coefficients, "FIR filter coefficients set correctly");
    check(filter.num_coefficients == num_coefficients, "FIR filter number of coefficients set correctly");
    check(filter.history.size == history_size, "FIR filter history buffer size set correctly");
    check(filter.history.head == 0, "FIR filter history buffer head initialized to 0");
    check(filter.history.count == 0, "FIR filter history buffer count initialized to 0");
    history_size = 2; // Insufficient history size
    result = fir_filter_init(&filter, coefficients, num_coefficients, history_storage, history_size);
    check(!result, "FIR filter initialization fails with insufficient history size");
    check(filter.coefficients == coefficients, "FIR filter coefficients remain unchanged after failed initialization");
    check(filter.num_coefficients == num_coefficients, "FIR filter number of coefficients remains unchanged after failed initialization");
    check(filter.history.size == 3, "FIR filter history buffer size remains unchanged after failed initialization");
    check(filter.history.head == 0, "FIR filter history buffer head remains unchanged after failed initialization");
    check(filter.history.count == 0, "FIR filter history buffer count remains unchanged after failed initialization");
}

void test_fir_filter_process_incomplete_history(void)
{
    FirFilter filter;
    const float coefficients[] = {0.25f, 0.5f, 0.25f};
    float history_storage[3];
    fir_filter_init(&filter, coefficients, 3,history_storage, 3);
    float output;
    output = fir_filter_process(&filter, 4.0f);
    check(output == 1.0f, "FIR ignores missing samples with one available sample");
    output = fir_filter_process(&filter, 8.0f);
    check(output == 4.0f, "FIR ignores missing samples with two available samples");
}
void test_fir_filter_process_complete_history(void)
{
    FirFilter filter;

    const float coefficients[] = {0.25f, 0.5f, 0.25f};
    float history_storage[3];

    fir_filter_init(&filter, coefficients, 3, history_storage, 3);

    float output;

    /* Fill the filter history with the first two samples. */
    fir_filter_process(&filter, 4.0f);

    check(filter.history.count == 1,"FIR history count after first sample");
    fir_filter_process(&filter, 8.0f);
    check(filter.history.count == 2,"FIR history count after second sample");
    /*
     * The history is now complete:
     *
     * y = 0.25(12) + 0.5(8) + 0.25(4) = 8
     */
    output = fir_filter_process(&filter, 12.0f);
    check(filter.history.count == 3,"FIR history count after third sample");
    check(output == 8.0f,"FIR output with complete history");
    /*
     * The history is full, so the oldest sample (4) is overwritten.
     * The history now represents:
     *
     * x[n]   = 16
     * x[n-1] = 12
     * x[n-2] = 8
     */
    output = fir_filter_process(&filter, 16.0f);
    check(filter.history.count == 3,"FIR history count remains at capacity after fourth sample");
    check(output == 12.0f,"FIR output after first history wraparound");

    /*
     * The history now represents:
     *
     * x[n]   = 20
     * x[n-1] = 16
     * x[n-2] = 12
     *
     * y = 0.25(20) + 0.5(16) + 0.25(12) = 16
     */
    output = fir_filter_process(&filter, 20.0f);
    check(filter.history.count == 3,"FIR history count remains at capacity after fifth sample");
    check(output == 16.0f,"FIR output remains correct after history wraparound");
}
int main (void) {
    test_fir_filter_init();
    test_fir_filter_process_incomplete_history();
    test_fir_filter_process_complete_history();
    return 0;
}