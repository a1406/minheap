#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "minheap.h"

bool cmp_int(void *a, void *b)
{
	int *aa = a;
	int *bb = b;
	if (*aa < *bb)
		return true;
	return false;
}

int main(int argc, char *argv[])
{
	struct minheap heap;
	init_heap(&heap, sizeof(int), 100, cmp_int);
	int data[100];
	for (int i = 0; i < 100; ++i)
	{
		data[i] = i;
		heap.nodes[i] = &data[i];
	}

	for (int i = 0; i < 100; ++i)
	{
		assert(i == get_node_index(&heap, &data[i]));
	}

	for (int i = 0; i < 100; i+=2)
	{
		push_heap(&heap, &data[i]);
	}
	for (int i = 1; i < 100; i+=2)
	{
		push_heap(&heap, &data[i]);
	}

	data[3] = 34;
	data[19] = 10;
	data[43] = 7;
	data[54] = 199;
	data[20] = -1;	
//	adjust_heap_node(&heap, &data[3]);
//	adjust_heap_node(&heap, &data[19]);
//	adjust_heap_node(&heap, &data[43]);
//	adjust_heap_node(&heap, &data[54]);
	adjust_heap_node(&heap, &data[20]);	

	int last = -0xffffff;
	int *ret;
	while (ret = pop_heap(&heap))
	{
		assert(*ret >= last);
		last = *ret;
		printf("ret = %d\n", *ret);
	}
	
    return 0;
}
