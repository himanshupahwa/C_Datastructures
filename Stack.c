#include <stdio.h>
#include <stdlib.h>
#include "Stack.h"

void init_stackdata(STACKDATA* stackData, void* data, int mem_size)
{
	stackData->data = malloc(sizeof(mem_size));
	stackData->next = NULL;
	stackData->prev = NULL;

	memcpy(stackData->data, data, mem_size) ;
}

void init_stack(STACKPTR stack, int mem_size)
{
	stack->top = NULL;
	stack->mem_size = mem_size;
	stack->size = 0;
}

void insert_stack(STACKPTR stack, void* data)
{
	STACKDATAPTR newStackData = (STACKDATAPTR) malloc(sizeof(STACKDATA));
	init_stackdata(newStackData, data, stack->mem_size);
	stack->size++;
	if(stack->top==NULL)
	{
		stack->top = newStackData;
	}
	else
	{
		newStackData->next = stack->top;
		stack->top = newStackData;
	}
}

STACKDATAPTR find_stack_node(STACKPTR stack,void* data)
{
	STACKDATA* temp = stack->top;
	while(temp != NULL)
	{
		if(data == temp->data)
		{
			return temp;
		}
		temp = temp->next;
	}
	return NULL;
}

STACKDATAPTR find_stack_prev_node(STACKPTR stack,void* data)
{
	STACKDATA* temp = stack->top;
	while(temp != NULL && temp->next != NULL)
	{
		if(data == temp->next->data)
		{
			return temp;
		}
		temp = temp->next;
	}
	return NULL;
}

BOOL delete_stack(STACKPTR stack,void *data)
{
	STACKDATA *node_to_delete;
	STACKDATA* prev_node_to_delete;
	
	prev_node_to_delete	= find_stack_prev_node(stack, data);
	if(prev_node_to_delete == NULL)
		return FALSE;
	node_to_delete		= prev_node_to_delete->next;
	prev_node_to_delete->next	= node_to_delete->next;
	free(node_to_delete);

	stack->size--;
	return TRUE;
}

int size_stack(STACKPTR stack)
{
	return stack->size;
}

void parse_stack(STACKPTR stack)
{
	STACKDATAPTR tempQNode = stack->top;
	while(tempQNode != NULL)
	{
		printf("%d,", *((int*)tempQNode->data)); // Override such functions based on data type
		tempQNode = tempQNode->next;
	}
}

void push(STACKPTR stack, void* data)
{
	STACKDATAPTR newQueueData = (STACKDATAPTR) malloc(sizeof(STACKDATA));
	init_stackdata(newQueueData, data, stack->mem_size);
	stack->size++;
	if(stack->top==NULL)
	{
		stack->top = newQueueData;

	}
	else
	{
		newQueueData->next = stack->top;
		stack->top = newQueueData;
	}
}

void pop(STACKPTR stack)
{
	STACKDATAPTR tempNode = NULL;
	if(stack->top == NULL)
		return;
	
	tempNode = stack->top->next;

	free(stack->top);
	stack->top = tempNode;
	stack->size--;
}



