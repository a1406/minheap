#include "minheap.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

static bool insert_heap(struct minheap *heap, int pos, void *node);
static void min_heap_shift_down_(min_heap_t* s, unsigned hole_index, void* node);
static void min_heap_shift_up_(min_heap_t* s, unsigned hole_index, void *node);
static void min_heap_shift_up_unconditional_(min_heap_t* s, unsigned hole_index, void* node);

int init_heap(struct minheap *heap, int max_size, minheap_cmp cmp)
{
	heap->max_size = max_size;
	heap->cur_size = 0;
	heap->nodes = malloc(sizeof(void *) * max_size);
	if (!heap->nodes)
		return (-1);
	heap->cmp = cmp;
	return (0);
}
int get_node_index(struct minheap *heap, void **node)
{
	int index = (node - &heap->nodes[0]) / sizeof(void *);
	assert(heap->cur_size > index);
	assert(heap->nodes[index] == node);
	return index;
}

int push_heap(struct minheap *heap, void *node)
{
	if (heap->cur_size >= heap->max_size)
		return (-1);
	min_heap_shift_up_(heap, heap->cur_size++, node);	
//	insert_heap(heap, heap->cur_size, node);
	return (0);
}
void *pop_heap(struct minheap *heap)
{
    if (heap->cur_size <= 0)
    {
        return NULL;
    }

    // 保存最小值
    void *ret = heap->nodes[0];
	min_heap_shift_down_(heap, 0u, heap->nodes[--heap->cur_size]);
	return ret;
/*
    // 比较两个子节点，将小的提升为父节点
    int parent = 0;
    int left, right;
    for (left = 2 * parent + 1, right = left + 1;
        right < heap->cur_size;
        left = 2 * parent + 1, right = left + 1)
    {
		if (heap->cmp(heap->nodes[left], heap->nodes[right]))
        {
			heap->nodes[parent] = heap->nodes[left];
			parent = left;
        }
        else
        {
			heap->nodes[parent] = heap->nodes[right];
			parent = right;			
        }
	}

    // 将最后一个节点填在空出来的节点上, 防止数组空洞
	if (parent != heap->cur_size - 1)
    {
			//因为insert_heap里面会+1，所以还需要额外-1
		insert_heap(heap, parent, heap->nodes[--heap->cur_size]);
    }

	--heap->cur_size;	
	return ret;
*/	
}
int adjust_heap_node(struct minheap *heap, void **node)
{
	int index = get_node_index(heap, node);
	unsigned parent = (index - 1) / 2;	

	if (index > 0 && heap->cmp(*node, heap->nodes[parent]))
		min_heap_shift_up_unconditional_(heap, index, *node);
	else
		min_heap_shift_down_(heap, index, *node);
	return 0;
}

int erase_heap_node(struct minheap* heap, void **node)
{
	int index = get_node_index(heap, node);
	void *last = heap->nodes[--heap->cur_size];
	unsigned parent = (index - 1) / 2;
	if (index > 0 && heap->cmp(last, heap->nodes[parent]))
		min_heap_shift_up_unconditional_(heap, index, last);
	else
		min_heap_shift_down_(heap, index, last);
	return (0);
}

/*
static bool insert_heap(struct minheap *heap, int pos, void *node)
{
	heap->nodes[pos] = node;

    // 依次和父节点比较，如果比父节点小，则上移
    int child, parent;
    for (child = pos, parent = (child - 1) / 2;
        child > 0;
        child = parent, parent = (child - 1) / 2)
    {
		if (heap->cmp(heap->nodes[child], heap->nodes[parent]))
		{
			void *tmp = heap->nodes[child];
			heap->nodes[child] = heap->nodes[parent];
			heap->nodes[parent] = tmp;
		}
		else
		{
			break;
		}
    }

    ++heap->cur_size;

    return true;
}
*/
static void min_heap_shift_up_unconditional_(min_heap_t* s, unsigned hole_index, void* node)
{
    unsigned parent = (hole_index - 1) / 2;
    do
    {
		s->nodes[hole_index] = s->nodes[parent];
		hole_index = parent;
		parent = (hole_index - 1) / 2;
    } while (hole_index && s->cmp(node, s->nodes[parent]));
    s->nodes[hole_index] = node;
}

static void min_heap_shift_up_(min_heap_t* s, unsigned hole_index, void *node)
{
    unsigned parent = (hole_index - 1) / 2;
    while (hole_index && s->cmp(node, s->nodes[parent]))
	{
		s->nodes[hole_index] = s->nodes[parent];
		hole_index = parent;
		parent = (hole_index - 1) / 2;
	}
	s->nodes[hole_index] = node;
}

static void min_heap_shift_down_(min_heap_t* s, unsigned hole_index, void* node)
{
    unsigned min_child = 2 * (hole_index + 1);
    while (min_child < s->cur_size)
	{
		if (min_child == s->cur_size - 1
			|| s->cmp(s->nodes[min_child - 1], s->nodes[min_child]))
			--min_child;
		if (s->cmp(node, s->nodes[min_child]))
			break;
		s->nodes[hole_index] = s->nodes[min_child];
		hole_index = min_child;
		min_child = 2 * (hole_index + 1);
	}
	s->nodes[hole_index] = node;
}
