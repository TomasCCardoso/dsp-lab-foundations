#include <stdio.h>
#include <stdbool.h>

#include "ring_buffer/ring_buffer.h"

void check(bool condition, const char *message) {
    if(condition) {
        printf("PASS: %s\n", message);
    } else {
        printf("FAIL: %s\n", message);
    }
}
void test_rb_init_state() {
    float storage[4];
    RingBuffer rb;
    rb_init(&rb, storage, 4);
    check(rb.size == 4, "Ring buffer initialized with correct size");
    check(rb.head == 0, "Ring buffer head initialized to 0");
    check(rb.count == 0, "Ring buffer count initialized to 0");
}

int main() {
    test_rb_init_state();
    return 0;
}