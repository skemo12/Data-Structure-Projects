#ifndef __HEAP_H__
#define __HEAP_H__

#include <stdlib.h>
#include <math.h>

/* We assume there is a defined primitive type Item. */
typedef struct {
	int prior; // Item priority
	Item data; // Item d
}ItemType;

typedef struct heap{
	long maxHeapSize; // capacity
	long size; // number of elements
	ItemType *elem; // array of elements
} PriQueue, *APriQueue;


PriQueue* makeQueue(int maxHeapSize){
	//TODO:

	APriQueue Queue = (APriQueue) calloc(1, sizeof(PriQueue));
	Queue->elem = (ItemType *) calloc(maxHeapSize, sizeof(ItemType));
	Queue->maxHeapSize = maxHeapSize;
	Queue->size = 0;
	return Queue;
}

int getLeftChild(int i){
	//TODO:
	int res = 2 * i + 1;
	return res;
}

int getRightChild(int i) {
	//TODO:
	int res = 2 * i + 2;
	return res;
}

int getParent(int i) {
	//TODO:
	int res = (i-1)/2;
	return res;
}

ItemType getMax(APriQueue h) {
	//TODO:
	return *(h->elem);
}

void siftUp(APriQueue h, int idx) {
	//TODO:
	if (idx == 0)
	{
		return;
	}
	if (idx > h->size)
	{
		return;
	}
	
	int parent = getParent(idx);
	if (h->elem[parent].prior > h->elem[idx].prior)
	{
		return;
	}
	
	ItemType aux = h->elem[parent];
	h->elem[parent] = h->elem[idx];
	h->elem[idx] = aux;
}


void insert(PriQueue *h, ItemType x) {
	
	if (h->size == h->maxHeapSize)
	{
		int newSize = h->maxHeapSize * 2;
		h->elem = (ItemType *) realloc(h->elem, newSize * sizeof(ItemType));
		h->maxHeapSize = newSize;
	}
	h->elem[h->size].data = x.data;
	h->elem[h->size].prior = x.prior;
	int parent = getParent(h->size);
	if (h->elem[parent].prior < h->elem[h->size].prior)
	{
		siftUp(h, h->size);
	}
	
	h->size++;
	
	//TODO:
}

void siftDown(APriQueue h, int idx){

	//TODO:
	if (idx > h->size)
	{
		return;
	}
	
	int leftChild = getLeftChild(idx);
	int rightChild = getRightChild(idx);
	int max = leftChild;
	if (h->size <= leftChild)
	{
		return;
	}
	
	if (h->size > rightChild && h->elem[leftChild].prior < h->elem[rightChild].prior)
	{
		max = rightChild;
	}


	ItemType aux = h->elem[max];
	h->elem[max] = h->elem[idx];
	h->elem[idx] = aux;

	int newLeftChild = getLeftChild(max);
	int newRightChild = getRightChild(max);
	
	if (newLeftChild < h->size && h->elem[idx].prior < h->elem[newLeftChild].prior)
	{
		siftDown(h, max);
	}
	else if (newRightChild < h->size)
	{
		if (h->elem[idx].prior < h->elem[newRightChild].prior)
		{
			siftDown(h, max);
		}
		
	}
	

}

void removeMax(APriQueue h) {

	//TODO:
	
	for (int i = 0; i < h->size - 1; i++)
	{
		h->elem[i] = h->elem[i + 1];
	}
	h->size--;
}

void freeQueue(APriQueue h){
	free(h->elem);
	free(h);
	// TODO:
}

#endif
