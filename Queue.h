#ifndef QUEUEDEF
#define QUEUEDEF

#include "DSUtils.h"

struct QueueData
{
	void* data;
	struct QueueData* next;
	struct QueueData* prev;
}; 

typedef struct QueueData QDATA;

void init_qdata(QDATA* qData, void* data, int mem_size);

struct QueueLS
{
	QDATA *head;
	QDATA *tail;
	int size;
	int mem_size;
};

typedef struct QueueLS QUEUE;


void init_queue(QUEUE* queue, int mem_size);
void insert_queue(QUEUE* queue, void* data);
QDATA* find_queue_node(QUEUE* queue, void* data);
QDATA* find_queue_prev_node(QUEUE* queue, void* data);
BOOL delete_queue(QUEUE* queue, void *data);
void parse_queue(QUEUE* queue);
void enqueue(QUEUE* queue, void* data);
void dequeue(QUEUE* queue);

#endif

