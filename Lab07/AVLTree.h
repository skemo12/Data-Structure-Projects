
#ifndef AVLTREE_H_
#define AVLTREE_H_

#include<stdlib.h>

// An AVL tree node
typedef struct AVLNode{
	Item elem;
	int height;
	struct AVLNode *l;
	struct AVLNode *r;
	struct AVLNode *p;

}AVLNode;

typedef struct AVLTree{
	long size;
	AVLNode* root;
	AVLNode* nil;
	int (*comp)(Item a, Item b);
}AVLTree;

AVLTree* avlCreateTree(int (*comp) (Item1,Item1))
{
	AVLTree* newTree = (AVLTree*) malloc(sizeof(AVLTree));
	newTree->comp = comp;
	newTree->nil = (AVLNode*) malloc(sizeof(AVLNode));
	newTree->nil->p = newTree->nil->l = newTree->nil->r = newTree->nil;
	newTree->nil->height = 0;
	newTree->root = (AVLNode*) malloc(sizeof(AVLNode));
	newTree->root->p = newTree->root->l = newTree->root->r = newTree->nil;
	newTree->root->height = 0;
	newTree->size = 0;

	return newTree;
}

int avlIsEmpty(AVLTree* tree){
	return (tree->root->l == tree->nil);
}

AVLNode* avlNewNode(AVLTree* tree){
	AVLNode* newNode = (AVLNode*) malloc(sizeof(AVLNode));
	// Initialize the new node to be used in the tree
	newNode->p = newNode->r = newNode->l = tree->nil;
	newNode->height = 1;

	return newNode;
}



// A utility function to get maximum of two integers
int max(int a, int b){
	return (a > b)? a : b;
}

// A utility function to right rotate subtree rooted with y
void avlRightRotate(AVLTree *tree,  AVLNode *y){
	
	//TO DO HERE
	AVLNode *parent = y->p;
	
	int s = 0;
	if (parent->l == y)
	{
		s = 1;
	}

	AVLNode *x = y->l;
	AVLNode *beta = x->r;
	y->l = beta;
	beta->p = y;
	x->r = y;
	y->p = x;
	x->p = parent;
	if (s)
	{
		parent->l = x;
	}
	else
	{
		parent->r = x;
	}
}

// A utility function to left rotate subtree rooted with x
void avlLeftRotate(AVLTree *tree, AVLNode *x){
	
	//TO DO HERE
	AVLNode *parent = x->p;
	int s = 0;
	if (parent->l == x)
	{
		s = 1;
	}
	
	AVLNode *y = x->r;
	AVLNode *beta = y->l;
	x->r = beta;
	beta->p = x;
	y->l = x;
	x->p = y;
	if (s)
	{
		parent->l = y;
	}
	else
	{
		parent->r = y;
	}
	y->p = parent;
}

// Get Balance factor of node x
int avlGetBalance(AVLNode *x){
	if (x == NULL)
		return 0;
	return x->l->height - x->r->height;
}

AVLNode * avlMinimum(AVLTree* tree, AVLNode* x){
	while (x->l != tree->nil)
		x = x->l;
	return x;
}

AVLNode* avlMaximum(AVLTree* tree, AVLNode* x){
	while(x->r != tree->nil){
		x = x->r;
	}
	return x;
}

int newBalance(AVLTree* tree, AVLNode *node)
{
	if (node == tree->nil)
	{
		return 0;
	}
	else 
	{
		return 1 + newBalance(tree, node->l) + newBalance(tree, node->r);
	}
	
}

AVLNode *searchParent(AVLTree *tree, AVLNode *node)
{
	AVLNode *root = tree->root->l;
	Item elem = node->elem;
	while (1)
	{
		if (*(root->elem) < *elem)
		{
			if (root->r != tree->nil)
			{
				root = root->r;
			}
			else
			{
				return root;
			}
			
		}
		else
		{
			if (root->l != tree->nil)
			{
				root = root->l;
			}
			else
			{
				return root;
			}
			
		}
		
	}
}

void avlInsert(struct AVLTree* tree, Item elem){
	
	//TO DO HERE
	if (tree->root->l == tree->nil)
	{
		tree->size = 1;
		AVLNode *newNode = avlNewNode(tree);
		newNode->p = tree->root;
		newNode->elem = elem;
		tree->root->l = newNode;
		tree->root->height = 0;
		tree->root->l->height = 0;
		tree->root->r->height = 0;
		return;
	}
	
	AVLNode *root = tree->root->l;
	AVLNode *newNode = avlNewNode(tree);
	newNode->height = 0;
	newNode->elem = elem;
	if (root->l == tree->nil && *(root->elem) > *elem)
	{
		root->l = newNode;
		newNode->p = root;
		tree->root->height--;
		return;
	}
	if (root->r == tree->nil && *(root->elem) < *elem)
	{
		root->r = newNode;
		newNode->p = root;
		root->r->height++;
		return;
	}
	
	root = searchParent(tree, newNode);
	
	int s = 1; //Adaugam in stanga sau in dreapta parintelui
	if (*(root->elem) < *elem)
	{
		s = 0;
	}
	
	int supS = 1; //Parintele este in stanga sau in dreapta parintelui sau
	if (root->p->r == root)
	{
		supS = 0;
	}

	newNode->p = root;
	AVLNode *supRoot = root->p;
	if (s)
	{
		root->l = newNode;
		int balance;
		balance = newBalance(tree, tree->root->l->l);
		balance -= newBalance(tree, tree->root->l->r);
		tree->root->height = balance;

		if (balance > -2 && balance < 2)
		{
			return;
		}
		
		if (supS)
		{
			avlRightRotate(tree,supRoot);
		}
		else
		{
			avlRightRotate(tree,root);
			avlLeftRotate(tree, supRoot);
		}
	}
	else
	{
		root->r = newNode;
		int balance;
		balance = newBalance(tree, tree->root->l->l);
		balance -= newBalance(tree, tree->root->l->r);
		tree->root->height = balance;

		if (balance > -2 && balance < 2)
		{
			return;
		}
		
		if (supS)
		{
			avlLeftRotate(tree, root);
			avlRightRotate(tree, supRoot);
		}
		else
		{
			avlLeftRotate(tree,supRoot);
		}
	}	
	
}




void avlDeleteNode(AVLTree *tree, AVLNode* node){
	destroyElem(node->elem);
	free(node);
}


void avlDestroyTreeHelper(AVLTree* tree, AVLNode* x) {
	if (x != tree->nil) {
		avlDestroyTreeHelper(tree,x->l);
		avlDestroyTreeHelper(tree,x->r);
		avlDeleteNode(tree,x);
	}
}

void avlDestroyTree(AVLTree* tree){
	avlDestroyTreeHelper(tree, tree->root->l);
	free(tree->root);
	free(tree->nil);
	free(tree);
}

#endif /* AVLTREE_H_ */