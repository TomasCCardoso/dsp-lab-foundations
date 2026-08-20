#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include <stdbool.h>

void check(bool condition, const char *message);
bool float_equal(float a, float b, float tolerance);

#endif