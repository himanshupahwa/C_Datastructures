#ifndef ARRAYHEAP
#define ARRAYHEAP
#include "DSUtils.h"

typedef struct HeapNode
{
	void* data;
} HEAPNODE;

typedef struct ArrayHeapImpl
{
	HEAPNODE *heapArray;
	int max_size;
	int current_size;

	int mem_size;

	BOOL (*fnCompareHeapNodeData)(void *heapNode1, void *heapNode2);
}ARRAYHEAPIMPL;

BOOL isEmpty(ARRAYHEAPIMPL* heapInst);

void init_heap(ARRAYHEAPIMPL* heapInst, int heapSize, int memSize, BOOL (*fnCompareHeapNodeDataPtr)(void *heapNode1, void *heapNode2));
void init_heapnode(HEAPNODE* heapNode,void* data,int mem_size);

BOOL insert_heap(ARRAYHEAPIMPL* heapInst, int key, int value);
void trickleUp(ARRAYHEAPIMPL* heapInst, int idx); // index of node that needs to be tricked up

void remove_heap(ARRAYHEAPIMPL* heapInst);
void trickleDown(ARRAYHEAPIMPL* heapInst, int idx);


void displayHeap(ARRAYHEAPIMPL* heapInst);



#endif 