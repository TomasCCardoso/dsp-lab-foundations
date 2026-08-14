#include <stdio.h>
#include <stdbool.h>

#include "ring_buffer/ring_buffer.h"
/**
 * @brief Reports the result of a test condition.
 *
 * Prints a PASS message when the condition evaluates to true
 * and a FAIL message otherwise.
 *
 * @param condition Boolean condition being evaluated.
 * @param message Description of the test being performed.
 */
void check(bool condition, const char *message) {
    if(condition) {
        printf("PASS: %s\n", message);
    } else {
        printf("FAIL: %s\n", message);
    }
}
/**
 * @brief Verifies the initial state of a RingBuffer after initialization.
 *
 * Checks that rb_init() correctly sets the buffer capacity, write
 * position and number of stored samples.
 */
void test_rb_init_state(void)
{
    float storage[4];
    RingBuffer rb;

    rb_init(&rb, storage, 4);

    check(rb.size == 4,
          "Ring buffer initialized with correct size");

    check(rb.head == 0,
          "Ring buffer head initialized to 0");

    check(rb.count == 0,
          "Ring buffer count initialized to 0");
}
/**
 * @brief Verifies rb_get() behaviour when the buffer contains no samples.
 *
 * An empty buffer must reject an attempt to retrieve a sample and
 * must not modify the RingBuffer state.
 */
void test_rb_get_empty(void)
{
    float storage[4];
    RingBuffer rb;

    rb_init(&rb, storage, 4);

    float out = 0.0f;
    bool result = rb_get(&rb, 0, &out);

    check(result == false,
          "rb_get returns false for empty buffer");

    check(rb.head == 0,
          "rb_get does not modify head on empty buffer");

    check(rb.count == 0,
          "rb_get does not modify count on empty buffer");
}

void test_rb_push(void) {
    float storage[4];
    RingBuffer rb;

    rb_init(&rb, storage, 4);
    rb_push(&rb, 10);

    float out = 0.0f;
    bool result = rb_get(&rb, 0, &out);

    check(result == true,
          "rb_get returns true after pushing a sample");
    
    check(out == 10.0f,
          "rb_get retrieves the correct sample after pushing");

    check(rb.head == 1,
          "rb_push advances head correctly");
    
    check(rb.count == 1,
          "rb_push increments count correctly");
          
    check(storage[0] == 10.0f,
      "rb_push stores the sample at the correct position");
}



int main() {
    test_rb_init_state();
    test_rb_get_empty();
    test_rb_push();
    return 0;
}