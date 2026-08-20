#include <stdio.h>
#include <stdbool.h>

#include "ring_buffer/ring_buffer.h"
#include "test_utils.h"


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

/**
 * @brief Verifies that multiple samples are stored and retrieved correctly.
 *
 * Pushes three samples into the RingBuffer and verifies:
 * - samples are stored at the expected storage positions;
 * - head advances correctly;
 * - count reflects the number of stored samples;
 * - rb_get() returns samples in reverse chronological order;
 * - accessing an unavailable sample returns false.
 */
void test_rb_push_multiple(void) 
{
    float storage[4];
    RingBuffer rb;

    rb_init(&rb, storage, 4);

    rb_push(&rb, 10.0f);
    rb_push(&rb, 20.0f);
    rb_push(&rb, 30.0f);

    /* Verify internal buffer state. */
    check(storage[0] == 10.0f,
          "rb_push stores the first sample correctly");

    check(storage[1] == 20.0f,
          "rb_push stores the second sample correctly");

    check(storage[2] == 30.0f,
          "rb_push stores the third sample correctly");

    check(rb.head == 3,
          "rb_push advances head correctly after multiple samples");

    check(rb.count == 3,
          "rb_push increments count correctly after multiple samples");

    /* Verify retrieval order. */
    float out = 0.0f;
    bool result;

    result = rb_get(&rb, 0, &out);
    check(result == true,
          "rb_get returns true for the most recent sample");
    check(out == 30.0f,
          "rb_get retrieves the most recent sample correctly");

    result = rb_get(&rb, 1, &out);
    check(result == true,
          "rb_get returns true for the second most recent sample");
    check(out == 20.0f,
          "rb_get retrieves the second most recent sample correctly");

    result = rb_get(&rb, 2, &out);
    check(result == true,
          "rb_get returns true for the third most recent sample");
    check(out == 10.0f,
          "rb_get retrieves the third most recent sample correctly");

    /* Verify access beyond the number of stored samples. */
    result = rb_get(&rb, 3, &out);
    check(result == false,
          "rb_get returns false when requesting an unavailable sample");
}

void test_rb_wraparound(void)
{
    float storage[4];
    RingBuffer rb;

    rb_init(&rb, storage, 4);

    /* Fill the buffer to capacity. */
    rb_push(&rb, 10.0f);
    rb_push(&rb, 20.0f);
    rb_push(&rb, 30.0f);
    rb_push(&rb, 40.0f);

    /* Push additional samples to cause wraparound. */
    rb_push(&rb, 50.0f);
    rb_push(&rb, 60.0f);

    /* Verify physical storage after wraparound. */
    check(storage[0] == 50.0f,
          "rb_push overwrites the oldest sample after wraparound");

    check(storage[1] == 60.0f,
          "rb_push overwrites the second oldest sample after wraparound");

    check(storage[2] == 30.0f,
          "rb_push preserves the third sample after wraparound");

    check(storage[3] == 40.0f,
          "rb_push preserves the fourth sample after wraparound");

    /* Verify RingBuffer state after wraparound. */
    check(rb.head == 2,
          "rb_push wraps head correctly");

    check(rb.count == 4,
          "rb_push keeps count at capacity after wraparound");

    /* Verify logical sample order. */
    float out = 0.0f;
    bool result;

    result = rb_get(&rb, 0, &out);
    check(result == true,
          "rb_get returns true for the most recent sample after wraparound");
    check(out == 60.0f,
          "rb_get retrieves the most recent sample correctly after wraparound");

    result = rb_get(&rb, 1, &out);
    check(result == true,
          "rb_get returns true for the second most recent sample after wraparound");
    check(out == 50.0f,
          "rb_get retrieves the second most recent sample correctly after wraparound");

    result = rb_get(&rb, 2, &out);
    check(result == true,
          "rb_get returns true for the third most recent sample after wraparound");
    check(out == 40.0f,
          "rb_get retrieves the third most recent sample correctly after wraparound");

    result = rb_get(&rb, 3, &out);
    check(result == true,
          "rb_get returns true for the fourth most recent sample after wraparound");
    check(out == 30.0f,
          "rb_get retrieves the fourth most recent sample correctly after wraparound");

    /* Verify access beyond the available samples. */
    result = rb_get(&rb, 4, &out);
    check(result == false,
          "rb_get returns false when accessing beyond buffer contents");
} 

/**
 * @brief Verifies that count increases until the buffer reaches capacity.
 *
 * Checks that count is incremented for each push while the buffer is
 * partially filled and remains equal to the buffer capacity once full.
 */

void test_rb_count_capacity(void)
{
    float storage[4];
    RingBuffer rb;

    rb_init(&rb, storage, 4);

    rb_push(&rb, 10.0f);
    check(rb.count == 1,
          "count is 1 after first push");

    rb_push(&rb, 20.0f);
    check(rb.count == 2,
          "count is 2 after second push");

    rb_push(&rb, 30.0f);
    check(rb.count == 3,
          "count is 3 after third push");

    rb_push(&rb, 40.0f);
    check(rb.count == 4,
          "count is 4 after fourth push (buffer full)");

    rb_push(&rb, 50.0f);
    check(rb.count == 4,
          "count remains at capacity after additional push");
}

int main() {
    test_rb_init_state(); //Initial State Test
    test_rb_get_empty(); //Empty Buffer Test
    test_rb_push(); //Single Push Test
    test_rb_push_multiple(); //Multiple Push Test
    test_rb_wraparound(); //Wraparound Test
    test_rb_count_capacity(); //Count and Capacity Test
    return 0;
}