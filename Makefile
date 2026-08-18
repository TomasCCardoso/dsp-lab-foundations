.PHONY: test clean
CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -I src

test: test_ring_buffer
	./test_ring_buffer
clean: 
	rm -f test_ring_buffer ring_buffer.o test_ring_buffer.o

ring_buffer.o: src/ring_buffer/ring_buffer.c src/ring_buffer/ring_buffer.h
	$(CC) $(CFLAGS) -c src/ring_buffer/ring_buffer.c -o ring_buffer.o

test_ring_buffer.o: tests/test_ring_buffer.c src/ring_buffer/ring_buffer.h
	$(CC) $(CFLAGS) -c tests/test_ring_buffer.c -o test_ring_buffer.o

test_ring_buffer: test_ring_buffer.o ring_buffer.o
	$(CC) test_ring_buffer.o ring_buffer.o -o test_ring_buffer


