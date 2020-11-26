#ifndef STACKDEF
#define STACKDEF

#include "DSUtils.h"

struct StackData
{
	void* data;
	struct StackData* next;
	struct StackData* prev;
}; 

typedef struct StackData STACKDATA;
typedef struct StackData * STACKDATAPTR;

void init_stackdata(STACKDATA* sData, void* data, int mem_size);

struct StackDataLS
{
	STACKDATA *top;
	int size;
	int mem_size;
};

typedef struct StackDataLS STACK;
typedef struct StackDataLS * STACKPTR;


void init_stack(STACKPTR stack, int mem_size);

void insert_stack(STACKPTR stack, void* data);
STACKDATAPTR find_stack_node(STACKPTR stack, void* data);
STACKDATAPTR find_stack_prev_node(STACKPTR stack, void* data);
BOOL delete_stack(STACKPTR stack, void *data);

void parse_stack(STACKPTR stack);

void push(STACKPTR stack, void* data);
void pop(STACKPTR stack);
int size_stack(STACKPTR stack);

#endif

