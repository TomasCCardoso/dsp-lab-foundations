.PHONY: test clean

test_ring_buffer: tests/test_ring_buffer.c src/ring_buffer/ring_buffer.c src/ring_buffer/ring_buffer.h
	gcc -Wall -Wextra -std=c11 -I src tests/test_ring_buffer.c src/ring_buffer/ring_buffer.c -o test_ring_buffer
test: test_ring_buffer
	./test_ring_buffer
clean: 
	rm -f test_ring_buffer

