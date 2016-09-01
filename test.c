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

	int *ret;
	while (ret = pop_heap(&heap))
		printf("ret %d\n", *ret);
	
    return 0;
}
