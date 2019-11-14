#include "BSearchTree.h"

void init_bsnode(BSTNODE* bstNode,void* data,int mem_size)
{
	bstNode->left	= NULL;
	bstNode->right	= NULL;
	bstNode->data	= malloc(mem_size);
	memcpy(bstNode->data, data, mem_size);

}

void init_bstree(BSTREE* bstree, int mem_size,BOOL (*fnCompareBSTNodeDataPtr)(void *bstNode1, void *bstNode2))
{
	bstree->root = NULL;
	bstree->mem_size =  mem_size;
	bstree->fnCompareBSTNodeData = fnCompareBSTNodeDataPtr; 
}

void insert_bst(BSTREE* bsTree, void* data)
{
	BOOL isLeftChild;
	BSTNODE *currentNode;
	BSTNODE *newNode;
	BSTNODE *parentNode;

	newNode = (BSTNODE*) malloc(sizeof(BSTNODE));
	init_bsnode(newNode, data, bsTree->mem_size);

	currentNode = bsTree->root;
	if(bsTree->root == NULL)
	{
		bsTree->root = newNode;
		return;
	}
	else
	{
		isLeftChild = FALSE;
		while(currentNode != NULL)
		{
			parentNode = currentNode;

			if(bsTree->fnCompareBSTNodeData(currentNode->data , data) == TRUE)
			{
				isLeftChild = TRUE;
				currentNode = currentNode->left;
			}
			else 
			{
				isLeftChild = FALSE;
				currentNode = currentNode->right;
			}
		}

		if(isLeftChild)
			parentNode->left = newNode;
		else
			parentNode->right = newNode;
	}
}

void inorder_traversal(BSTNODE* root)
{
	if(root == NULL)
		return;

	inorder_traversal(root->left);
	printf("%d\t", *((int*)(root->data)));
	inorder_traversal(root->right);
}

void preorder_traversal(BSTNODE* root)
{
	if(root == NULL)
		return;

	printf("%d\t", *((int*)(root->data)));
	preorder_traversal(root->left);
	preorder_traversal(root->right);
}

void postorder_traversal(BSTNODE* root)
{
	if(root == NULL)
		return;

	postorder_traversal(root->left);
	postorder_traversal(root->right);
	printf("%d\t", *((int*)(root->data)));
}

void dfs(BSTNODE* root)
{
	if(root == NULL)
		return;

	dfs(root->left);
	printf("%d\t", *((int*)(root->data)));
	dfs(root->right);
}

void bfs(QUEUE* depthNodes)
{
	int noOfNodes;
	int index;

	noOfNodes = depthNodes->size;
	index = 0;
	
	for(index = 0; index < noOfNodes ; index++)
	{
		int deficeit = 0;
		printf("%d\t",*((int*)((BSTNODE*)(depthNodes->tail->data))->data));
		((BSTNODE*)(depthNodes->tail->data))->left != NULL ? enqueue(depthNodes,((BSTNODE*)(depthNodes->tail->data))->left): deficeit++;
		((BSTNODE*)(depthNodes->tail->data))->right != NULL ? enqueue(depthNodes,((BSTNODE*)(depthNodes->tail->data))->right) : deficeit++;
		dequeue(depthNodes);
	}

	if(depthNodes->size > 0)
	{
		printf("\n");
		bfs(depthNodes);
	}
	else
	{
		printf("\n");
		return;
	}

}

