#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/types.h>
#include <unistd.h>
#include "minheap.h"

bool cmp_int(void *a, void *b)
{
	int *aa = a + sizeof(int);
	int *bb = b + sizeof(int);
	if (*aa < *bb)
		return true;
	return false;
}

int get_index(void *a)
{
	int *aa = a;
	return *aa;
}

void set_index(int index, void *a)
{
	int *aa = a;
	*aa = index;
}

struct data
{
	int index;
	int data;
};

bool cmp_int_simple(void *a, void *b)
{
	int *aa = a;
	int *bb = b;
	if (*aa < *bb)
		return true;
	return false;
}
void set_int_simple(int index, void *a)\
{
}

void test_simple()
{
	struct minheap heap;
	int data[100];	
	init_heap(&heap, 100, cmp_int_simple, NULL, set_int_simple);
	for (int i = 0; i < 100; ++i)
	{
		data[i] = i;
	}

	for (int i = 0; i < 100; i+=2)
	{
		push_heap(&heap, &data[i]);
	}
	for (int i = 1; i < 100; i+=2)
	{
		push_heap(&heap, &data[i]);
	}
	int last = -0xffffff;
	int *ret;
	while (ret = pop_heap(&heap))
	{
		assert(*ret >= last);
		last = *ret;
	}
}

void check_minheap(struct minheap *heap)
{
	int last = INT32_MIN;
	struct data *ret;
	while (ret = pop_heap(heap))
	{
		assert(ret->data >= last);
		last = ret->data;
	}
}
static struct data data[100];	
void test_push(struct minheap *heap)
{
	for (int i = 0; i < 100; ++i)
	{
		data[i].data = rand();
		push_heap(heap, &data[i]);		
	}
	check_minheap(heap);
}
void test_erase(struct minheap *heap)
{
	for (int i = 0; i < 100; ++i)
	{
		data[i].data = rand();
		push_heap(heap, &data[i]);		
	}
	
	for (int i = 0; i < 100; i += 2)
	{
		assert(erase_heap_node(heap, &data[i]) == 0);		
	}	
	check_minheap(heap);

	for (int i = 0; i < 100; ++i)
	{
		data[i].data = rand();
		push_heap(heap, &data[i]);		
	}
	
	for (int i = 1; i < 100; i += 2)
	{
		assert(erase_heap_node(heap, &data[i]) == 0);		
	}	
	check_minheap(heap);
}

void test_adjust(struct minheap *heap)
{
	for (int i = 0; i < 100; ++i)
	{
		data[i].data = rand();
		push_heap(heap, &data[i]);		
	}

	for (int i = 0; i < 100; ++i)
	{
		data[i].data = rand();
		adjust_heap_node(heap, &data[i]);		
	}
	
	check_minheap(heap);
}

int main(int argc, char *argv[])
{
	struct minheap heap;
	init_heap(&heap, 100, cmp_int, get_index, set_index);
	for (int i = 0; i < 100; ++i)
	{
		data[i].data = i;
	}

	srand(getpid());

	for (int i = 0; i < 100; i+=2)
	{
		push_heap(&heap, &data[i]);
	}
	for (int i = 1; i < 100; i+=2)
	{
		push_heap(&heap, &data[i]);
	}

	data[3].data = 34;
	data[19].data = 10;
	data[43].data = 7;
	data[54].data = 199;
	data[20].data = -1;

	adjust_heap_node(&heap, &data[3]);
	adjust_heap_node(&heap, &data[19]);
	adjust_heap_node(&heap, &data[43]);
	adjust_heap_node(&heap, &data[54]);
	adjust_heap_node(&heap, &data[20]);	

	check_minheap(&heap);
//	test_simple();

	int test_count = 10000;
	if (argv[1])
		test_count = atoi(argv[1]);

	for (int i = 0; i < test_count; ++i)
	{
		test_push(&heap);
		test_erase(&heap);
		test_adjust(&heap);
	}
	
    return 0;
}
