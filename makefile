all: test

test: test.c minheap.c
	gcc -g -O0 -o test test.c minheap.c
