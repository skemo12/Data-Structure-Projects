/*
*	Created by Nan Mihai on 28.03.2021
*	Copyright (c) 2021 Nan Mihai. All rights reserved.
*	Laborator 5 - Structuri de date
*	Facultatea de Automatica si Calculatoare
*	Anul Universitar 2020-2021, Seria CD
*/
#include "tree.h"

/*
*	Funcție care creează un arbore cu un singur nod
*/
Tree createTree(Item value) {
	Tree root = malloc(sizeof(TreeNode));
	root->value = value;
	root->left = NULL;
	root->right = NULL;
	return root;
}

/*
*	Funcție care inițializează un nod de arbore
*		- îi alocă memorie
*		- îi setează câmpul valoare
*		- setează left și right să pointeze către NULL
*/
void init(Tree *root, Item value) {
	// TODO 1
	*root = createTree(value);
}

/*
*	Funcție care inserează o valoare într-un arbore binar, respectând
* proprietățile unui arbore binar de căutare
*/
Tree insert(Tree root, Item value) {
	// TODO 2
	if (root == NULL)
	{
		root = createTree(value);
	}
	else
	{
		Tree tree = root;
		Tree prev;
		while (tree != NULL)
		{
			prev = tree;
			if (value == prev->value)
			{
				return root;
			}

			if (value > tree->value)
			{
				tree = tree->right;
			}
			else
			{
				tree = tree->left;
			}
			
		}
		
		
		if (value > prev->value)
		{
			prev->right = createTree(value);
		}
		else
		{
			prev->left = createTree(value);
		}
		
		
	}
	
	return root;
}

/*
*	Funcție care afișează nodurile folosind parcurgerea în postordine
*/
void printPostorder(Tree root) {
	// TODO 3
	if (root != NULL)
	{
		printPostorder(root->left);
		printPostorder(root->right);
		printf("%d ",root->value);
	}
	
}

/*
*	Funcție care afișează nodurile folosind parcurgerea în preordine
*/
void printPreorder(Tree root) {
	// TODO 4
	if (root != NULL)
	{
		printf("%d ",root->value);
		printPreorder(root->left);
		printPreorder(root->right);	
	}		
}

/*
*	Funcție care afișează nodurile folosind parcurgerea în inordine
*/
void printInorder(Tree root) {
	// TODO 5
	if (root != NULL)
	{
		printInorder(root->left);
		printf("%d ",root->value);
		printInorder(root->right);	
	}
}

/*
*	Funcție care dealocă întreaga memorie alocată pentru un arbore binar
*		- root va pointa către NULL după ce se va apela funcția
*/
void freeTree(Tree *root) {
	// TODO 6
	if (*root != NULL)
	{
		freeTree(&(*root)->left);
		freeTree(&(*root)->right);
		Tree aux = *root;
		*root = NULL;
		free(aux);		
	}
	
}


/*
*	Funcție care determină numărul de noduri dintr-un arbore binar
*/
int size(Tree root) {
	// TODO 7
	if (root == NULL)
	{
		return 0;
	}
	else
	{
		return 1 + size(root->left) + size(root->right);
	}
	
	
	return -1;
}

/*
*	Funcție care returnează adâncimea maximă a arborelui
*/
int max (int a, int b)
{
	if (a > b)
	{
		return a;
	}
	else
	{
		return b;
	}
	
}
int maxDepth(Tree root) {
	// TODO 8
	if (root == NULL)
	{
		return -1;
	}
	else
	{
		return 1 + max(maxDepth(root->left),maxDepth(root->right));
	}
	
}

/*
*	Funcție care construiește oglinditul unui arbore binar
*/
void mirror(Tree root) {
	// TODO 9
	if (root != NULL)
	{
		mirror(root->left);
		Tree aux = root->left;
		root->left = root->right;
		root->right = aux;
		mirror(root->left);
	}
	
}

/*
*	Funcție care verifică dacă doi arbori binari sunt identici
*/
int sameTree(Tree root1, Tree root2) {
	// TODO 10
	if (root1 != NULL || root2 != NULL)
	{
		if (root1->value != root2->value)
		{
			return 0;
		}
		sameTree(root1->left, root2->left);
		sameTree(root1->right, root2->right);
		
	}
	return 1;
}
