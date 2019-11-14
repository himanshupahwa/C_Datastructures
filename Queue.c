#include "Queue.h"

void init_qdata(QDATA* qData, void* data, int mem_size)
{
	qData->next = NULL;
	qData->prev = NULL;
	qData->data  = malloc(mem_size);

	memcpy(qData->data, data, mem_size);
}

void init_queue(QUEUE* queue, int mem_size)
{
	queue->head = NULL;
	queue->mem_size = mem_size;
	queue->tail = NULL;
	queue->size = 0;
}

void insert_queue(QUEUE* queue, void* data)
{
	QDATA* newQueueData = (QDATA*) malloc(sizeof(QDATA));
	init_qdata(newQueueData, data, queue->mem_size);

	if(queue->head==NULL)
	{
		queue->head = newQueueData;
		queue->tail = queue->head;
	}
	else
	{
		queue->tail->next = newQueueData;
		queue->tail = queue->tail->next;
	}
	queue->size++;
}

QDATA* find_queue_node(QUEUE* queue, void* data)
{
	QDATA* temp = queue->head;
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

QDATA* find_queue_prev_node(QUEUE* queue, void* data)
{
	QDATA* temp = queue->head;
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

BOOL delete_queue(QUEUE* queue, void *data)
{
	QDATA *node_to_delete;
	QDATA* prev_node_to_delete;
	
	prev_node_to_delete	= find_queue_prev_node(queue, data);
	if(prev_node_to_delete == NULL)
		return FALSE;
	node_to_delete		= prev_node_to_delete->next;
	prev_node_to_delete->next	= node_to_delete->next;
	free(node_to_delete);
	queue->size--;
	return TRUE;
}

void parse_queue(QUEUE* queue)
{
	QDATA *temp = queue->head;
	while(temp != NULL)
	{
		printf("%d\t",*((int*)(temp->data)));
		temp = temp->next;
	}
}

void enqueue(QUEUE* queue, void* data)
{
	QDATA* newQueueData = (QDATA*) malloc(sizeof(QDATA));
	init_qdata(newQueueData, data, queue->mem_size);

	if(queue->head==NULL)
	{
		queue->head = newQueueData;
		queue->tail = queue->head;
	}
	else
	{
		newQueueData->next = queue->head;
		queue->head = newQueueData;
	}
	queue->size++;
}

void dequeue(QUEUE* queue)
{
	QDATA* temp_node;
	QDATA* prev_temp_node;
	QDATA* q_node_to_delete;

	temp_node = queue->head;
	prev_temp_node = queue->head;
	q_node_to_delete = NULL;

	if(queue->tail==NULL)
	{
		printf("ERROR : tail cannot be NULL on dequeue...Deletion forfieted...");
	}
	else if(queue->head == queue->tail)
	{
		free(q_node_to_delete);
		queue->head = NULL;
		queue->tail = NULL;
		queue->size--;
	}
	else
	{
		q_node_to_delete = queue->tail;
		while(temp_node!=queue->tail)
		{
			prev_temp_node = temp_node;
			temp_node	   = temp_node->next;
		}
		if(prev_temp_node != q_node_to_delete)
		{
			prev_temp_node->next = NULL;
		}
		queue->size--;
		queue->tail = prev_temp_node;
		free(q_node_to_delete);

	}
}

