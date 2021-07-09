/*
*	Created by Nan Mihai on 05.05.2021
*	Copyright (c) 2020 Nan Mihai. All rights reserved.
*	Laborator 6 - Structuri de date
*	Grupa 314CD
*	Facultatea de Automatica si Calculatoare
*	Anul Universitar 2020-2021, Seria CD
*/
#include "tree.h"

/*
*	Funcție care creează un arbore cu un singur nod
*/
Tree createTree(Tree parent, Item value) {
	Tree root = malloc(sizeof(TreeNode));
	root->parent = parent;
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
void init(Tree *root, Tree parent, Item value) {
	// TODO 0
	*root = createTree(parent, value);
}

/*
*	Funcție care inserează o valoare într-un arbore binar, respectând
* proprietățile unui arbore binar de căutare
*/
Tree insert(Tree root, Item value) {
	// TODO 1
	if (root == NULL)
	{
		return createTree(NULL,value);
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
			prev->right = createTree(prev, value);
		}
		else
		{
			prev->left = createTree(prev, value);
		}
	}
	
	
	
	return root;
}


/*
*	Funcție care verifică dacă un arbore este vid sau nu
*		- întoarce 1 dacă arborele este vid
*		- întoarce 0 dacă arborele nu este vid
*/
int isEmpty(Tree root) {
	// TODO 2
	if (root == NULL)
	{
		return 1;
	}
	
	return 0;
}

/*
*	Funcție care verifică dacă o valoare există sau nu în arbore
*		- 1 dacă value există în arbore
*		- 0 dacă value nu există în arbore
*/
int contains(Tree tree, Item value) {
	// TODO 3
	
	if (tree == NULL)
	{
		return 0;
	}
	else
	{
		
		if (tree->value == value)
		{
			return 1;
		}

		if (value > tree->value)
		{
			contains(tree->right, value);
		}
		else
		{ 
			contains(tree->left, value);
		}
		
	}
	
}

/*
*	Funcție care determină elementul minim dintr-un arbore binar de căutare
*		- NULL pentru arbore vid
*/
Tree minimum(Tree tree) {
	// TODO 4.1
	if (tree == NULL)
	{
		return NULL;
	}

	while (tree->left != NULL)
	{
		tree = tree->left;
	}
	
	return tree;
}

/*
*	Funcție care determină elementul maxim dintr-un arbore binar de căutare
*		- NULL pentru arbore vid
*/
Tree maximum(Tree tree) {
	// TODO 4.2

	if (tree == NULL)
	{
		return NULL;
	}
	
	while (tree->right != NULL)
	{
		tree = tree->right;
	}
	
	return tree;
}

/*
*	Funcție care determină succesorul în inordine pentru nodul care conține
* valoarea value.
*/
Tree successor(Tree root, Item value) {
	// TODO 5
	if (!contains(root, value))
	{
		return NULL;
	}
	Tree tree = root;
	while (tree->value != value)
	{
		if (value > tree->value)
		{
			tree = tree->right;
		}
		else
		{
			tree = tree->left;
		}
		
	}
	if (tree->right == NULL)
	{
		while (tree != NULL)
		{
			if (tree->value > value)
			{
				break;
			}
			
			tree = tree->parent;
		}
		return tree;
	}
	
	return minimum(tree->right);
}

/*
*	Funcție care determină predecesorul în inordine pentru nodul care conține
* valoarea value.
*/
Tree predecessor(Tree root, Item value) {
	// TODO 6
	if (!contains(root, value))
	{
		return NULL;
	}
	Tree tree = root;
	while (tree->value != value)
	{
		if (value > tree->value)
		{
			tree = tree->right;
		}
		else
		{
			tree = tree->left;
		}
		
	}
	if (tree->left == NULL)
	{
		while (tree != NULL)
		{
			if (tree->value < value)
			{
				break;
			}
			
			tree = tree->parent;
		}
		return tree;
	}
	
	return maximum(tree->left);
}

/*
*	Funcție care dealocă întreaga memorie alocată pentru un arbore binar
*		- root va pointa către NULL după ce se va apela funcția
*/
void destroyTree(Tree *root) {
	// TODO
	if (*root != NULL)
	{
		destroyTree(&(*root)->left);
		destroyTree(&(*root)->right);
		Tree aux = *root;
		*root = NULL;
		free(aux);		
	}
	
}

/*
*	Funcție care șterge un nod cu o anumită valoare din arbore
*/
Tree delete(Tree root, Item value) {
	// TODO 7

	if (root == NULL)
	{
		return root; 
	}
	if (root->value > value)
	{
		root->left = delete(root->left, value);
	}
	else if (root->value < value)
	{
		root->right = delete(root->right, value);
	}
	else if (root->right != NULL && root->left != NULL)
	{
		Tree aux = minimum(root->right);
		root->value = aux->value;
		root->right = delete(root->right, aux->value);
	}
	else
	{
		Tree aux = root;
		if (root->left != NULL)
		{
			root = root->left;
		}
		else
		{
			root = root->right;
		}
		free(aux);
		
	}
	
	
	return root;
}

/*
*	Funcție care determină cel mai apropiat strămoș comun pentru
* două noduri având cheile value1 și value2
*/
Tree lowestCommonAncestor(Tree root, Item value1, Item value2) {
	// TODO 8
	
	if (!contains(root, value1) && !contains(root, value2))
	{
		return NULL;
	}
	
	Tree tree1 = root, tree2 = root;
	while (tree1->value != value1)
	{
		if (value1 > tree1->value)
		{
			tree1 = tree1->right;
		}
		else
		{
			tree1 = tree1->left;
		}
		
	}
	while (tree2->value != value2)
	{
		if (value2 > tree2->value)
		{
			tree2 = tree2->right;
		}
		else
		{
			tree2 = tree2->left;
		}
		
	}
	int ok = 0;
	Tree res;
	Tree parent1 = tree1;
	Tree parent2 = tree2;
	while (ok == 0)
	{
		if (contains(parent1,value2))
		{
			ok = 1;
			res = parent1;
		}
		else if (contains(parent2,value1))
		{
			ok = 1;
			res = parent2;
		}
		else
		{
			if (parent1 != NULL)
			{
				parent1 = parent1->parent;
			}
			
			if (parent1 != NULL)
			{
				parent2 = parent2->parent;
			}
		}
		
		
	}
	
	return res;
}
