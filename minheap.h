#ifndef MINHEAP_H
#define MINHEAP_H

#include <stdbool.h>

typedef bool (*minheap_cmp)(void *a, void *b);

typedef struct minheap
{
	int max_size;
	int cur_size;
	void **nodes;
	int data_size;
	minheap_cmp cmp;
} min_heap_t;

int init_heap(struct minheap *heap, int data_size, int max_size, minheap_cmp cmp);
int get_node_index(struct minheap *heap, void *node);

int push_heap(struct minheap *heap, void *node);
void *pop_heap(struct minheap *heap);
int adjust_heap_node(struct minheap *heap, void *node);

#endif /* MINHEAP_H */
