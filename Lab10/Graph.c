#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Util.h"
#include "Graph.h"

TGraphL* createGraphAdjList(int numberOfNodes) {
	//TODO: 1
	TGraphL* graph = (TGraphL *) calloc(1, sizeof(TGraphL));
	graph->adl = (ATNode *) calloc(numberOfNodes, sizeof(ATNode));

	for (int i = 0; i < numberOfNodes; i++)
	{
		graph->adl[i] = NULL;
	}
	
	graph->nn = numberOfNodes;
	return graph;
}

void addEdgeList(TGraphL* graph, int v1, int v2) {

	//TODO: 1
	int ok1 = 0, ok2 = 0;
	if (!ok1 && graph->adl[v1] == NULL)
	{
		graph->adl[v1] = (ATNode) calloc(1,sizeof(TNode));
		graph->adl[v1]->v = v2;
		graph->adl[v1]->next = NULL;
		ok1 = 1;
	}

	if (!ok2 && graph->adl[v2] == NULL)
	{
		graph->adl[v2] = (ATNode) calloc(1,sizeof(TNode));
		graph->adl[v2]->v = v1;
		graph->adl[v2]->next = NULL;
		ok2 = 1;
	}
	
	if (!ok1 && graph->adl[v1] != NULL && graph->adl[v1]->next == NULL)
	{
		ATNode newNode1 = (ATNode) calloc(1,sizeof(TNode));
		newNode1->next = NULL;
		newNode1->v = graph->adl[v1]->v;
		graph->adl[v1]->next = newNode1;
		graph->adl[v1]->v = v2;
		ok1 = 1;
	}


	if (!ok2 && graph->adl[v2] != NULL && graph->adl[v2]->next == NULL)
	{
		ATNode newNode2 = (ATNode) calloc(1,sizeof(TNode));
		newNode2->next = NULL;
		newNode2->v = graph->adl[v2]->v;
		graph->adl[v2]->next = newNode2;
		graph->adl[v2]->v = v1;
		ok2 = 1;
	}
	
	if (!ok1 && graph->adl[v1] != NULL && graph->adl[v1]->next != NULL)
	{
		ATNode newNode1 = (ATNode) calloc(1,sizeof(TNode));
		newNode1->next = graph->adl[v1]->next;
		newNode1->v = graph->adl[v1]->v;
		graph->adl[v1]->next = newNode1;
		graph->adl[v1]->v = v2;
		ok1 = 1;
	}
	
	if (!ok2 && graph->adl[v2] != NULL && graph->adl[v2]->next != NULL)
	{
		ATNode newNode2 = (ATNode) calloc(1,sizeof(TNode));
		newNode2->next = graph->adl[v2]->next;;
		newNode2->v = graph->adl[v2]->v;
		graph->adl[v2]->next = newNode2;
		graph->adl[v2]->v = v1;
		ok2 = 2;
	}

}

List* dfsIterative(TGraphL* graph, int s) {
	//TODO: 2
	
	List *path = createList();
	Stack *stiva = createStack();
	ATNode node = NULL;
	int *vizitat = (int *) calloc(2 * graph->nn, sizeof(int));
	push(stiva, s);

	while (!isStackEmpty(stiva))
	{
		int n = top(stiva);
		pop(stiva);
		
		vizitat[n] = 1;
		enqueue(path, n);
		
		node = graph->adl[n];
		while (node != NULL)
		{
			int vecin = node->v;
			
			if (vizitat[vecin] == 0)
			{
				push(stiva, vecin);
				vizitat[vecin] = 1;
			}
			node = node->next;
		}		
	}

	destroyStack(stiva);
	free(vizitat);
	return path;

}

void dfsRecHelper(TGraphL* graph, int* visited, List* path, int s) {
	//TODO: 3
	visited[s] = 1;
	enqueue(path, s);
	ATNode node = graph->adl[s];
	while (node != NULL)
	{
		int vecin = node->v;
		if (visited[vecin] == 0)
		{
			dfsRecHelper(graph, visited, path, vecin);
		}
		
		node = node->next;
	}
	
}

List* dfsRecursive(TGraphL* graph, int s) {
	// TODO 3
	int *visited = (int *) calloc(graph->nn, sizeof(int));
	List *path = createList();

	dfsRecHelper(graph, visited, path, s);
	free(visited);
	return path;
}

List* bfs(TGraphL* graph, int s){
	// TODO: 4

	List *path = createList();
	Queue *coada = createQueue();
	int *vizitat = (int *) calloc(graph->nn, sizeof(int));
	ATNode node = NULL;
	vizitat[s] = 1;
	enqueue(coada, s);

	while (!isQueueEmpty(coada))
	{
		int n = front(coada);
		dequeue(coada);
		enqueue(path, n);

		node = graph->adl[n];
		while (node != NULL)
		{
			int vecin = node->v;
			if (vizitat[vecin] == 0)
			{
				enqueue(coada, vecin);
				vizitat[vecin] = 1;
			}
			
			node = node->next;
		}
		
	}
	free(vizitat);
	destroyQueue(coada);
	return path;
}

void destroyGraphAdjList(TGraphL* graph){
	// TODO: 5
	for (int i = 0; i < graph->nn; i++)
	{
		ATNode node = graph->adl[i];
		while (node != NULL)
		{
			ATNode last = node;
			node = node->next;
			free(last);
		}
		
	}
	free(graph->adl);
	free(graph);
}

void removeEdgeList(TGraphL* graph, int v1, int v2){
	TNode* it = graph->adl[v1];
	TNode* prev = NULL;
	while(it != NULL && it->v != v2){
		prev = it;
		it = it->next;
	}

	if(it == NULL)return;

	if(prev != NULL)
		prev->next = it->next;
	else
		graph->adl[v1] = it->next;
	free(it);

	it = graph->adl[v2];
	prev = NULL;
	while(it != NULL && it->v != v1){
		prev = it;
		it = it->next;
	}
	if(it == NULL) return;
	if(prev != NULL)
		prev->next = it->next;
	else
		graph->adl[v2] = it->next;

	free(it);
}

void removeNodeList(TGraphL* graph, int v){
	for(int i = 0; i < graph->nn;i++){
		removeEdgeList(graph,v,i);
	}
}
