#include "DSUtils.h"

BOOL compareIntData(void *bstNode1, void *bstNode2)
{
	int *data1 = (int*) bstNode1;
	int *data2 = (int*) bstNode2;

	return (*data1 > *data2 ? TRUE: FALSE);

}