#include "minheap.h"
#include <stdlib.h>
#include <string.h>

static bool insert_heap(struct minheap *heap, int pos, void *node);

int init_heap(struct minheap *heap, int data_size, int max_size, minheap_cmp cmp)
{
	heap->max_size = max_size;
	heap->cur_size = 0;
	heap->nodes = malloc(sizeof(void *) * max_size);
	if (!heap->nodes)
		return (-1);
	heap->data_size = data_size;
	heap->cmp = cmp;
	return (0);
}
int get_node_index(struct minheap *heap, void *node)
{
	return (node - heap->nodes[0]) / heap->data_size;
}

int push_heap(struct minheap *heap, void *node)
{
	if (heap->cur_size >= heap->max_size)
		return (-1);
	insert_heap(heap, heap->cur_size, node);
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
}
int adjust_heap_node(struct minheap *heap, void *node)
{
	
	return (0);
}

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
