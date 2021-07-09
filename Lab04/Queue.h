#ifndef QUEUE_H_
#define QUEUE_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct QueueNode{
	Item elem;
	struct QueueNode *next;
}QueueNode;

typedef QueueNode TcelQ;
typedef QueueNode *ACelQ;

typedef struct Queue{
	QueueNode *front;
	QueueNode *rear;
	long size;
}Queue;

typedef Queue TCoada;
typedef Queue *AQ;


Queue* createQueue(void){
	// TODO: Cerinta 2
	AQ coada = (AQ ) calloc(1,sizeof(TCoada));
	coada->front = NULL;
	coada->rear = NULL;
	coada->size = 0;
	return coada;
} 

int isQueueEmpty(Queue *q){
	// TODO: Cerinta 2
	if (q->front == NULL && q->rear == NULL && q->size == 0)
	{
		return 1;
	}
	return 0;
}

void enqueue(Queue *q, Item elem){
	// TODO: Cerinta 2
	ACelQ node = (ACelQ ) calloc(1,sizeof(TcelQ));
	node->elem = elem;
	node->next = NULL;
	if (isQueueEmpty(q))
	{
		q->front = node;
		q->rear = node;

	}
	else
	{
		q->rear->next = node;
		q->rear = node;
	}
	q->size++;

}

Item front(Queue* q){
	// TODO: Cerinta 2
	return q->front->elem;
}

void dequeue(Queue* q){
	// TODO: Cerinta 2
	ACelQ node = q->front;
	q->size--;

	if (q->front == NULL || q->rear == NULL)
	{
		return;
	}
	
	if (q->front == q->rear)
	{
		free(q->front);
		q->front = NULL;
		q->rear = NULL;
		return;
	}
	q->front = node->next;
	free(node);
	

}

void destroyQueue(Queue *q){
	// TODO: Cerinta 2
	ACelQ node;
	while (q->front != NULL)
	{
		node = q->front;
		q->front = q->front->next;
		free(node);
	}
	free(q);
	
}

#endif
