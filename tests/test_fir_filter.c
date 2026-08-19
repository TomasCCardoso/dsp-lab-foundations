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

int main (void) {
    test_fir_filter_init();
    return 0;
}