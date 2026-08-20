.PHONY: test clean
CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -I src

test: test_ring_buffer test_fir_filter
	./test_ring_buffer
	./test_fir_filter
clean: 
	rm -f test_ring_buffer ring_buffer.o test_ring_buffer.o fir_filter.o test_fir_filter.o test_fir_filter

ring_buffer.o: src/ring_buffer/ring_buffer.c src/ring_buffer/ring_buffer.h
	$(CC) $(CFLAGS) -c src/ring_buffer/ring_buffer.c -o ring_buffer.o

test_ring_buffer.o: tests/test_ring_buffer.c src/ring_buffer/ring_buffer.h
	$(CC) $(CFLAGS) -c tests/test_ring_buffer.c -o test_ring_buffer.o

test_ring_buffer: test_ring_buffer.o ring_buffer.o
	$(CC) test_ring_buffer.o ring_buffer.o -o test_ring_buffer

fir_filter.o: src/fir_filter/fir_filter.c src/fir_filter/fir_filter.h src/ring_buffer/ring_buffer.h
	$(CC) $(CFLAGS) -c src/fir_filter/fir_filter.c -o fir_filter.o

test_fir_filter.o: tests/test_fir_filter.c src/fir_filter/fir_filter.h src/ring_buffer/ring_buffer.h
	$(CC) $(CFLAGS) -c tests/test_fir_filter.c -o test_fir_filter.o

test_fir_filter: test_fir_filter.o fir_filter.o ring_buffer.o
	$(CC) test_fir_filter.o fir_filter.o ring_buffer.o -o test_fir_filter



