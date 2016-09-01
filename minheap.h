#ifndef MINHEAP_H
#define MINHEAP_H

#include <stdbool.h>

struct minheap
{
	int max_size;
	int cur_size;
	void **nodes;
};

typedef bool (*minheap_cmp)(void *a, void *b);
int push_heap(void *data);

#endif /* MINHEAP_H */
