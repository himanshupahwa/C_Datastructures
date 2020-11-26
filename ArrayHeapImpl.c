#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "HeapArrayImpl.h"
#include "Queue.h"

void init_heapnode(HEAPARRAYNODEPTR heapArrayData, void * data, int mem_size)
{
	heapArrayData->key = malloc(mem_size);
	memcpy(heapArrayData->key, data, mem_size);
}

void init_heap(HEAPPTR heap, int max_size, int mem_size, BOOL (*fnCompareHeapNodeData)(void *heapNode1, void *heapNode2))
{
	heap->currentSize = 0;
	heap->maxSize = max_size;
	heap->heapArray = (HEAPARRAYNODEPTR *)malloc(max_size * (sizeof(HEAPARRAYNODE)));
	heap->mem_size = mem_size;
	heap->fnCompareHeapNodeData = fnCompareHeapNodeData;
}

void trickleUp(HEAPPTR heap, int idx)
{
	int parentIdx = (idx-1)/2;

	HEAPARRAYNODEPTR currentNode = heap->heapArray[idx];
	HEAPARRAYNODEPTR parentNode = heap->heapArray[parentIdx];

	while( idx > 0 && heap->fnCompareHeapNodeData(currentNode->key , parentNode->key)) // min or max heap 
	{
		heap->heapArray[idx] = heap->heapArray[parentIdx];
		idx = parentIdx;
		parentIdx = (idx-1)/2;
	}

	heap->heapArray[idx] = currentNode;
}

void trickleDown(HEAPPTR heap, int idx)
{
	int largerChildIdx;

	HEAPARRAYNODEPTR currentNode = heap->heapArray[idx];

	while(idx < heap->currentSize/2) // will run as long as idx is not at the bottom of the row ( has atleast one child)
	{
		int leftChildIdx = 2*idx + 1;
		int rightChildIdx = 2*idx + 2;

		if(heap->fnCompareHeapNodeData(heap->heapArray[leftChildIdx], heap->heapArray[rightChildIdx]))
			largerChildIdx = rightChildIdx;
		else
			largerChildIdx = leftChildIdx;

		if(heap->fnCompareHeapNodeData(currentNode ,heap->heapArray[largerChildIdx]))
			break;

		heap->heapArray[idx] = heap->heapArray[largerChildIdx];
		idx = largerChildIdx;
	}
}

BOOL insert_heap(HEAPPTR heap, void* data)
{
	HEAPARRAYNODEPTR heapNode = (HEAPARRAYNODEPTR)malloc(heap->mem_size);
	init_heapnode(heapNode, data, heap->mem_size);

	if(heap->currentSize >= heap->maxSize)
		return FALSE;

	heap->heapArray[heap->currentSize] = heapNode;
	trickleUp(heap, heap->currentSize);

	heap->currentSize++;
	return TRUE;
}


BOOL remove_heap(HEAPPTR heap)
{
	HEAPARRAYNODEPTR nodeToDelete = heap->heapArray[0];

	heap->heapArray[0] = heap->heapArray[heap->currentSize];
	heap->currentSize--;
	trickleDown(heap, 0);

	return TRUE;
}

void displayHeap(HEAPPTR heap)
{
	QUEUE queue;
	int currentIdxValue;
	int currentDepth;
		int tabCount;
	int leftChildIdx;
	int rightChildIdx;
	int heapIdx					= 0;
	int maxDepth				= (int)ceil(log((double)heap->currentSize));
	int nodeCountAtMaxDepth		= (int)(4*pow(2.0,maxDepth));
	int prevDepth = 0;
	int index;

	init_queue(&queue, sizeof(int));


	insert_queue(&queue, &heapIdx);
	while(queue.size > 0)
	{
		heapIdx = *((int*)queue.tail->data);
		dequeue(&queue);
		currentIdxValue = *((int*)(heap->heapArray[heapIdx]->key));

		currentDepth = (int) (log((double)heapIdx+1)/log(2.0));
		if(prevDepth < currentDepth)
			printf("\n");

		prevDepth = currentDepth;

		tabCount = nodeCountAtMaxDepth / (currentDepth+1);
		for(index = 0; index < tabCount; index++)
			printf("  ");
		printf("%d",currentIdxValue);

		leftChildIdx = 2*heapIdx + 1;
		rightChildIdx = 2*heapIdx + 2;

		if(leftChildIdx < heap->currentSize)
			enqueue(&queue, &leftChildIdx);

		if(rightChildIdx < heap->currentSize)
			enqueue(&queue, &rightChildIdx);
	}
}
