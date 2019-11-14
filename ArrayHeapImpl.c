#include "ArrayHeap.h"
#include "Queue.h"
#include <math.h>

void init_heapnode(HEAPNODE* heapNode,void* data,int mem_size)
{
	heapNode->data	= malloc(mem_size);
	memcpy(heapNode->data, data, mem_size);
}

void init_heap(ARRAYHEAPIMPL* heapInst, int heapSize, int memSize, BOOL (*fnCompareHeapNodeDataPtr)(void *heapNode1, void *heapNode2))
{
	heapInst->max_size = heapSize;
	heapInst->mem_size = memSize;
	heapInst->heapArray = (HEAPNODE *) malloc(sizeof(HEAPNODE)*heapSize);
	heapInst->current_size = -1;
	heapInst->fnCompareHeapNodeData = fnCompareHeapNodeDataPtr; 
}

BOOL isEmpty(ARRAYHEAPIMPL* heapInst)
{
	return ( heapInst->current_size == 0 ? TRUE : FALSE);
}

BOOL insert_heap(ARRAYHEAPIMPL* heapInst, int key, int value)
{
	if(heapInst->current_size == heapInst->max_size)
		return FALSE;


	init_heapnode(&(heapInst->heapArray[heapInst->current_size+1]), &value, heapInst->mem_size);

	// Trickle up the node inserted to top of heap
	trickleUp(heapInst, heapInst->current_size+1);
	heapInst->current_size++; // increment post trickleUp

	return TRUE;
}

void trickleUp(ARRAYHEAPIMPL* heapInst, int idx) // index of node that needs to be tricked up
{
	int parentIdx = (idx-1)/2;
	HEAPNODE nodeToInsert = heapInst->heapArray[idx];

	// loop as long as we havet reacged the root abd idx parent is less than new node
	while(idx > 0 && heapInst->fnCompareHeapNodeData(heapInst->heapArray[parentIdx].data , nodeToInsert.data) == FALSE) // This logic is for min heap
	{
		heapInst->heapArray[idx] = heapInst->heapArray[parentIdx];
		idx = parentIdx;
		parentIdx = (parentIdx - 1)/2;
	}

	heapInst->heapArray[idx] = nodeToInsert;
}

void remove_heap(ARRAYHEAPIMPL* heapInst)
{
	HEAPNODE node = heapInst->heapArray[0];
	heapInst->current_size--;
	heapInst->heapArray[0] = heapInst->heapArray[heapInst->current_size];

	trickleDown(heapInst, 0);
}

void trickleDown(ARRAYHEAPIMPL* heapInst, int idx)
{
	int largerChildIdx;

	HEAPNODE top = heapInst->heapArray[idx];

	while(idx < heapInst->current_size/2) // will run as long as idx is not at the bottom of the row ( has atleast one child)
	{
		int leftChildIdx = 2*idx + 1;
		int rightChildIdx = 2*idx + 2;

		if(heapInst->fnCompareHeapNodeData(heapInst->heapArray[leftChildIdx].data , heapInst->heapArray[rightChildIdx].data) == FALSE)
			largerChildIdx = rightChildIdx;
		else
			largerChildIdx = leftChildIdx;

		if(heapInst->fnCompareHeapNodeData(top.data , heapInst->heapArray[largerChildIdx].data) == TRUE)
			break;

		heapInst->heapArray[idx] = heapInst->heapArray[largerChildIdx];
		idx = largerChildIdx;
	}
}


void displayHeap(ARRAYHEAPIMPL* heapInst)
{
	int heapIdx					= 0;
	int maxDepth				= (int)ceil(log((double)heapInst->current_size));
	int nodeCountAtMaxDepth		= (int)(4*pow(2.0,maxDepth));
	int prevDepth = 0;
	QUEUE queue;
	int currentIdxValue;
	int currentDepth;
	int tabCount;
	int leftChildIdx;	
	int rightChildIdx;	
	int index;
	init_queue(&queue, sizeof(int));

	enqueue(&queue, &heapIdx);

	while(queue.size > 0)
	{
		int heapIdx = *((int*)(queue.tail->data));
		dequeue(&queue);

		currentIdxValue = *((int*)((heapInst->heapArray[heapIdx]).data));

		currentDepth = (int) (log((double)(heapIdx+1))/log(2.0));
		if(prevDepth < currentDepth)
			printf("\n");

		prevDepth = currentDepth;

		tabCount = nodeCountAtMaxDepth / (currentDepth+1);
		for(index = 0; index < tabCount; index++)
			printf("  ");

		printf("%d", currentIdxValue);

		leftChildIdx	= 2*heapIdx + 1;
		rightChildIdx	= 2*heapIdx + 2;

		if(leftChildIdx < heapInst->current_size+1)
			enqueue(&queue, &leftChildIdx);

		if(rightChildIdx < heapInst->current_size+1)
			enqueue(&queue, &rightChildIdx);

	}
}

