#ifndef HEAPARRAYIMPL
#define HEAPARRAYIMPL

#include "DSUtils.h"


typedef struct HeapArrayNode {
	void *key;

} HEAPARRAYNODE;

typedef HEAPARRAYNODE * HEAPARRAYNODEPTR;

void init_heapnode(HEAPARRAYNODEPTR heapArryData, void * data, int mem_size);

typedef struct HeapArray {
	HEAPARRAYNODEPTR * heapArray;
	int maxSize;
	int currentSize;

	int mem_size;
	BOOL (*fnCompareHeapNodeData)(void *heapNode1, void *heapNode2);

}HEAP;

typedef HEAP * HEAPPTR;

void init_heap(HEAPPTR heap, int max_size, int mem_size, BOOL (*fnCompareHeapNodeData)(void *heapNode1, void *heapNode2));

void trickleDown(HEAPPTR heap, int idx);
void trickleUp(HEAPPTR heap, int idx);

BOOL insert_heap(HEAPPTR heap, void* data);
BOOL remove_heap(HEAPPTR heap);


void displayHeap(HEAPPTR heap);


#endif

