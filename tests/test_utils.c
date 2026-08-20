#include "test_utils.h"
#include <math.h>
#include <stdio.h>

bool float_equal(float a, float b, float tolerance) {
    return fabsf(a - b) < tolerance;
}

void check(bool condition, const char *message) {
    if(condition) {
        printf("PASS: %s\n", message);
    } else {
        printf("FAIL: %s\n", message);
    }
}
