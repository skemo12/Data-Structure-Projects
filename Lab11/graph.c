#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "heap.h"

#define MAX 999
typedef int TCost;

typedef struct node
{
	int v;
	TCost c;
	struct node *next;
} TNode, *ATNode;

typedef struct
{
	int nn;
	ATNode *adl;
}	TGraphL;


void alloc_list(TGraphL * G, int n)
{
    int i;
    G->nn = n;
	G->adl = (ATNode*) malloc((n+1)*sizeof(ATNode));
	for(i = 0; i < n; i++)
		G->adl[i] = NULL;

}

void free_list(TGraphL *G)
{
    int i;
    ATNode it;
    for(i = 1; i < G->nn; i++){
		it = G->adl[i];
		while(it != NULL){
			ATNode aux = it;
			it = it->next;
			free(aux);
		}
		G->adl[i] = NULL;
	}
	G->nn = 0;
}

void insert_edge_list(TGraphL *G, int v1, int v2, int c)
{
 TNode *t;
 t=(ATNode)malloc(sizeof(TNode));
 t->v = v2; t->c=c; t->next = G->adl[v1]; G->adl[v1]=t;
 t=(ATNode)malloc(sizeof(TNode));
 t->v = v1;  t->c=c; t->next = G->adl[v2]; G->adl[v2]=t;
}

void printDistances(int *dist, int n)
{
    printf("Varf	Drum minim\n");
    for (int i = 0; i < n; i++)
    {
		printf("%d	%d\n", i, dist[i]);
	}
}

void dijkstra(TGraphL G, int s)
{
	int V = G.nn;
    MinHeap *heap = newQueue(V);
	int *dist = (int *) calloc(V, sizeof(int));
	
	for (int v = 0; v < V; v++)
	{
		dist[v] = MAX;
		heap->elem[v] = newNode(v, dist[v]);
		heap->pos[v] = v;
	}

	heap->elem[s] = newNode(s, dist[s]);
	heap->pos[s] = s;
	dist[s] = 0;

	decreaseKey(heap, s,dist[s]);
	heap->size = V;

	while (!isEmpty(heap))
    {
        MinHeapNode *minHeapNode = removeMin(heap);
        int u = minHeapNode->v;
 
        ATNode vecin = G.adl[u];
        while (vecin != NULL)
        {
            int v = vecin->v;
 
            if (isInMinHeap(heap, v) && dist[u] != MAX &&
              								vecin->c + dist[u] < dist[v])
            {
                dist[v] = dist[u] + vecin->c;
                decreaseKey(heap, v, dist[v]);
            }
            vecin = vecin->next;
        }
    }
 
    printDistances(dist, V);
	free(dist);
}

void printPrim(int *parent, int V)
{
	printf("Parinte	Varf\n");
    for (int i = 1; i < V; i++)
    {
		printf("%d	%d\n", parent[i], i);
	}
}

void Prim(TGraphL G)
{
	int V = G.nn;
    int *parent = (int *) calloc(V, sizeof(int));
    int *key = (int *) calloc(V, sizeof(int));
  
    MinHeap *heap = newQueue(V);
    for (int v = 1; v < V; v++) {
        parent[v] = -1;
        key[v] = MAX;
        heap->elem[v] = newNode(v, key[v]);
        heap->pos[v] = v;
    }

    key[0] = 0;
    heap->elem[0] = newNode(0, key[0]);
    heap->pos[0] = 0;
  
    heap->size = V;
  
    while (!isEmpty(heap)) 
	{
        MinHeapNode *minHeapNode = removeMin(heap);
        int u = minHeapNode->v; 

        ATNode vecin = G.adl[u];
        while (vecin != NULL) 
		{
            int v = vecin->v;

            if (isInMinHeap(heap, v) && vecin->c < key[v]) 
			{
                key[v] = vecin->c;
                parent[v] = u;
                decreaseKey(heap, v, key[v]);
            }
            vecin = vecin->next;
        }
    }

    printPrim(parent, V);
	free(key);
	free(parent);
}


int main()
{
    int i,v1,v2,c;
	int V,E;
	TGraphL G;
	ATNode t;
	freopen ("graph.in", "r", stdin);
	scanf ("%d %d", &V, &E);
	alloc_list(&G, V);

	for (i=1; i<=E; i++)
	{
		scanf("%d %d %d", &v1, &v2, &c);
	    insert_edge_list(&G, v1,v2, c);
	}

	for(i=0;i<G.nn;i++)
	{
    	printf("%d : ", i);
    	for(t = G.adl[i]; t != NULL; t = t->next)
   			 printf("%d ",t->v);
    		 printf("\n");
	}
	dijkstra(G,0);
	Prim(G);

	return 0;
}