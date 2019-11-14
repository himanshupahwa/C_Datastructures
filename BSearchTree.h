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

typedef struct BinarySearchTree
{
	BSTNODE *root;
	int mem_size;
	BOOL (*fnCompareBSTNodeData)(void *bstNode1, void *bstNode2);
}BSTREE;

void init_bsnode(BSTNODE* bstNode);
void init_bsnode(BSTNODE* bstNode,void* data,int mem_size, BOOL (*fnCompareBSTNodeData)(void *bstNode1, void *bstNode2));

void init_bstree(BSTREE* bstree);
void insert_bst(BSTREE* root, int key, int value);
void inorder_traversal(BSTNODE* root);
void preorder_traversal(BSTNODE* root);
void postorder_traversal(BSTNODE* root);
void dfs(BSTREE* root);
void bfs(QUEUE* depthNodes);

#endif
