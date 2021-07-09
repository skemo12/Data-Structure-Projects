#ifndef STACK_H_
#define STACK_H_

#include <stdio.h>
#include <stdlib.h>



typedef struct StackNode{
	Item elem;
	struct StackNode *next;
}StackNode;

typedef StackNode TCelSt; // Redenumirea unui nod la notatiile din curs 
typedef StackNode *ACelSt; // Redenumirea unui pointer la nod la notatiile din curs

typedef struct Stack{
	StackNode* head;  // Varful stivei
	long size; // Numarul de elemente din stiva
}Stack;

typedef Stack TStiva; // Redenumirea stivei la notatiile din curs
typedef Stack *ASt;//  // Redenumirea unui pointer la stiva la notatiile din curs

Stack* createStack(void){
	// TODO: Cerinta 1
	ASt stiva = (ASt ) calloc(1,sizeof(TStiva));
	stiva->size = 0;
	stiva->head = NULL;

	return stiva;
}

int isStackEmpty(Stack* stack){
	// TODO: Cerinta 1
	if (stack->size == 0 && stack->head == NULL)
	{
		return 1;
	}
	return 0;
}

void push(Stack *stack, Item elem){
	// TODO: Cerinta 1
	ACelSt node = (ACelSt ) calloc(1,sizeof(TCelSt));
	node->elem = elem;
	if (isStackEmpty(stack))
	{
		node->next = NULL;
		stack->head = node;
	}
	else
	{
		node->next = stack->head;
		stack->head = node;
	}
	stack->size++;
}

Item top(Stack *stack){	
	// TODO: Cerinta 1
	return stack->head->elem;
} 

void pop(Stack *stack){
	// TODO: Cerinta 1
	ACelSt node = stack->head;
	stack->head = stack->head->next;
	free(node);
	stack->size--;

}

void destroyStack(Stack *stack){
	// TODO: Cerinta 1
	while (!isStackEmpty(stack))
	{
		pop(stack);
	}
	free(stack);
}

#endif 
