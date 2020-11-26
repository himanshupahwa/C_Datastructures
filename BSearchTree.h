#ifndef BSEARCHTREE
#define BSEARCHTREE

#include "DSUtils.h"
#include "Queue.h"

typedef struct BinarySearchTreeNode
{
	void* data;
	struct BinarySearchTreeNode *left;
	struct BinarySearchTreeNode *right;

	
} BSTNODE;

typedef BSTNODE * BSTNODEPTR;

typedef struct BinarySearchTree
{
	BSTNODE *root;
	int mem_size;
	BOOL (*fnCompareBSTNodeData)(void *bstNode1, void *bstNode2);
}BSTREE;

typedef BSTREE * BSTREEPTR;

//void init_bsnode(BSTNODE* bstNode);
void init_bsnode(BSTNODE* bstNode,void* data,int mem_size);

//void init_bstree(BSTREE* bstree);
void init_bstree(BSTREEPTR bstree, int mem_size, BOOL (*fnCompareBSTNodeDataPtr)(void *bstNode1, void *bstNode2));

void insert_bst(BSTREEPTR root, void* key);
void inorder_traversal(BSTNODEPTR root);
void preorder_traversal(BSTNODEPTR root);
void postorder_traversal(BSTNODEPTR root);
void dfs(BSTNODEPTR root);
void bfs(QUEUE* depthNodes);

#endif
