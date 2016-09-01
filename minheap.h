#ifndef MINHEAP_H
#define MINHEAP_H

#include <stdbool.h>

typedef bool (*minheap_cmp)(void *a, void *b);

struct minheap
{
	int max_size;
	int cur_size;
	void **nodes;
	minheap_cmp cmp;
};

int push_heap(void *node, struct minheap *heap);
void *pop_heap(struct minheap *heap);
int adjust_heap_node(struct minheap *heap, void *node);

#endif /* MINHEAP_H */
