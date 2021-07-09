#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 1024

typedef struct node
{
    int v;
	struct node *next;
    
} TNode, *ATNode;

typedef struct graf
{
    int nn;
    char **name;
    ATNode *adl; 

}Graph, *TGraph;

int getIdx(TGraph G, char *name)
{
    // Gets index of name in graph
    for (int i = 0; i < G->nn; i++)
    {
        if (strcmp(G->name[i], name) == 0)
        {
            return i;
        }
        
    }
    
    return -1;
}

ATNode newAdjListNode(int v)
{
    // Creates new node
    ATNode newNode = (ATNode) calloc(1, sizeof(TNode));
    newNode->v = v;
    newNode->next = NULL;
    
    return newNode;
}

void addEdge(TGraph graph, int idx, int v)
{
    // Adds directed edge to a graph
    ATNode newNode = newAdjListNode(v);
    newNode->next = graph->adl[idx];
    graph->adl[idx] = newNode;
}

void delEdge(TGraph G, int a, int b)
{
    //Deletes directed edge
    ATNode node = G->adl[a];
    ATNode last = node;
    
    while (node != NULL)
    {
        if(node->v == b)
        {
            ATNode toBeDel = node;
            node = node->next;
            last->next = node;
            
            if (toBeDel == G->adl[a])
            {
                G->adl[a] = node;
            }
            
            free(toBeDel);
            toBeDel = NULL;
        }

        if (node == NULL)
        {
            break;
        }
        
        last = node;
        node = node->next;
    }
    
}

TGraph createGraph(int V)
{
    // Allocates memory for a graph
    TGraph G = (TGraph) calloc(1, sizeof(Graph));
    G->nn = V;
    G->adl = (ATNode *) calloc(V, sizeof(ATNode));
    G->name = (char **) calloc(V, sizeof(char*));

    return G;
}

TGraph getGraph(FILE *input)
{
    // Reads a graph from input file
    int V, L;
    // Maximun length of of a name;
    fscanf(input, "%d %d", &V, &L);
    int nameSize = 2 * MAX_SIZE / V;
    TGraph G = createGraph(V);

    for (int i = 0; i < V; i++)
    {
        char buffer[MAX_SIZE];
        fscanf(input, "%s", buffer);
        G->name[i] = (char *) calloc(nameSize, sizeof(char));
        strcpy(G->name[i], buffer);
    }
    
    for (int i = 0; i < L; i++)
    {
        char el1[nameSize], el2[nameSize];
        fscanf(input, "%s %s", el1, el2);
        int idx1 = getIdx(G, el1);
        int idx2 = getIdx(G, el2);

        addEdge(G, idx1, idx2);
        
    }
    
    return G;
}

int dfsRecHelper(TGraph graph, int* visited, int v, int *verify) 
{
	if (visited[v] == 0)
    {
        visited[v] = 1;
        verify[v] = 1;

        ATNode node = graph->adl[v];
        while (node != NULL)
        {
            if (!visited[node->v] && dfsRecHelper(graph, visited, node->v, verify))
            {
                return 1;
            }
            else
            {
                if (verify[node->v])
                {
                    return 1;
                }
            
            }
            node = node->next;
        }
    }
    verify[v] = 0;
    return 0;
	
}

int checkForCycles(TGraph graph)
{
    //Checks for cycles in a Graph
	int *visited = (int *) calloc(graph->nn, sizeof(int));
    int *verify = (int *) calloc(graph->nn, sizeof(int));

    for (int i = 0; i < graph->nn; i++)
    {
        visited[i] = 0;
        verify[i] = 0;
    }
    

	int ok = 1;
    for (int i = 0; i < graph->nn; i++)
    {
        
        ATNode node = graph->adl[i];
        while (node != NULL)
        {
            node = node->next;
        }
        if(dfsRecHelper(graph, visited, i, verify))
        {
            ok = 0;
        }
    }
    
	free(visited);
    free(verify);
	return ok;
}

void destroyGraph(TGraph graph)
{
    // Destroys Graph
	for (int i = 0; i < graph->nn; i++)
	{
        free(graph->name[i]);
		ATNode node = graph->adl[i];
		while (node != NULL)
		{
			ATNode last = node;
			node = node->next;
			free(last);
		}
		
	}
	free(graph->adl);
    free(graph->name);
	free(graph);
}

TGraph cloneGraph(TGraph G)
{
    // Clones a Graph
    int V = G->nn;
    TGraph clone = createGraph(V);
    for (int i = 0; i < V; i++)
    {
        int len = strlen(G->name[i]);
        clone->name[i] = (char *) calloc(len + 1, sizeof(char));
        strcpy(clone->name[i], G->name[i]);
    }
    
    for (int i = 0; i < V; i++)
    {
        ATNode node = G->adl[i];
        while (node != NULL)
        {
            addEdge(clone, i, node->v);
            node = node->next;
        }
    }
    
    return clone;
}

void searchPathHelper(TGraph G, int* visited, int s, int *ok, int idxB)
{
    if ((*ok) == 1)
    {
        return;
    }
    visited[s] = 1;
	ATNode node = G->adl[s];
    if(s == idxB)
    {
        (*ok) = 1;
        return;
    }
	while (node != NULL)
	{
		int vecin = node->v;
		if (visited[vecin] == 0)
		{
			searchPathHelper(G, visited, vecin, ok, idxB);
		}
		
		node = node->next;
	}
    
}

void searchPath(TGraph G, int idxA, int idxB, int *ok)
{
    // Searches for a path from idxA to idxB
    int V = G->nn;
    (*ok) = 0;

    int *visited = (int *) calloc(V, sizeof(int));
    searchPathHelper(G,visited, idxA, ok, idxB);
    free(visited);
}

int *getParents(TGraph G, int idx)
{
    // Gets all parents for node idx
    int *parents = (int *) calloc(G->nn, sizeof(int));
    for (int i = 0; i < G->nn; i++)
    {
        if (i == idx)
        {
            continue;
        }
        
        ATNode node = G->adl[i];
        while (node != NULL)
        {
            if(node->v == idx)
            {
                parents[i]++;
            }
            node = node->next;
        }
        
        
    }
    return parents;
}

int **AllParents(TGraph G)
{
    // Creeaza o matrice pentru a identifica usor toti parintii unui nod
    // Nodul j este parinte al lui i daca all[i][j] == 1;
    int V = G->nn;
    int **all = (int **) calloc(V, sizeof(int *));

    for (int i = 0; i < V; i++)
    {
        all[i] = getParents(G, i);
    }
    return all;

}

void markAllParents(TGraph G, int **allParent, int *allNodes, int idx)
{
    // Marcheaza toti stramosii unui nod in allnodes
    int V = G->nn;
    for (int i = 0; i < V; i++)
    {
        if (i == idx)
        {
            continue;
        }
        if (allParent[idx][i] == 1)
        {
            allNodes[i] = 1;
            markAllParents(G,allParent, allNodes, i);
        }
        
    }
    
}

TGraph createAncestral(TGraph G, int **allParents, int *allNodes)
{
    //Creates the Ancestral Graph
    TGraph clone = cloneGraph(G);
    int V = clone->nn;
    for (int i = 0; i < V; i++)
    {
        
        if (allNodes[i] == 0)
        {
            for (int j = 0; j < V; j++)
            {
                if (allParents[i][j])
                {
                    delEdge(clone, j , i);
                }
                
            }
            
            ATNode node = clone->adl[i];
            while (node != NULL)
            {
                ATNode next = node->next;
                delEdge(clone, i, node->v);
                if (node == NULL)
                {
                    break;
                }
                node = next;
            }
            
        }   
    }
    return clone;
}

TGraph multipleParents(TGraph clone)
{
    // Step 2 of solving the problem, treating the case of nodes with 
    // more than 2 parents
    int V = clone->nn;
    for (int i = 0; i < V; i++)
    {
        int *localParents = getParents(clone , i);
        int nrParinti = 0;
        for (int j = 0; j < V; j++)
        {
            if (localParents[j])
            {
                nrParinti++;
            }
            
        }
        
        if (nrParinti > 1)
        {
            for (int j = 0; j < V; j++)
            {
                if (localParents[j])
                {
                    for (int k = j + 1; k < V; k++)
                    {
                        if (localParents[k])
                        {
                            delEdge(clone, j, k);
                            delEdge(clone, k, j);
                            addEdge(clone, j, k);
                            addEdge(clone, k, j);
                        }
                        
                    }
                    
                }
                
            }
            
        }
        free(localParents);
    }
    return clone;
}

TGraph convertToUndirected(TGraph clone)
{
    // Convert directed graph into undirected
    int V = clone->nn;

    TGraph undirected = createGraph(V);
    
    for (int i = 0; i < V; i++)
    {
        ATNode node = clone->adl[i];
        while (node != NULL)
        {
            int E = node->v;
            ATNode next = node->next;
            delEdge(clone, i, E);
            delEdge(clone, E, i);
            addEdge(undirected, E, i);
            addEdge(undirected, i, E);
            node = next;
        }
        
    }
    return undirected;
}

TGraph deleteObserved(TGraph undirected, int *obsNumbers)
{
    // Deletes all nodes from obsNumers
    int V = undirected->nn;
    for (int i = 0; i < V; i++)
    {
        if (obsNumbers[i] == 0)
        {
            continue;
        }
        
        ATNode node = undirected->adl[i];
        while (node != NULL)
        {
            ATNode next = node->next;
            int E = node->v;
            delEdge(undirected, i, E);
            delEdge(undirected, E, i);
            node = next;
        }
        
    }
    return undirected;
}

int checkDependency(char *A, char *B, char **observed, int lenObs, TGraph G)
{
    int V = G->nn;
    int **allParents = AllParents(G);

    int idxA = getIdx(G, A);
    int idxB = getIdx(G, B);

    int *obsNumbers;
    
    if (observed == NULL)
    {
        obsNumbers = NULL;
    }
    else
    {
        obsNumbers = (int *) calloc(V, sizeof(int));
        for (int i = 0; i < lenObs; i++)
        {
            int index = getIdx(G, observed[i]);
            obsNumbers[index] = 1;
        }
    }
    // All nodes that will not be deleted
    int *allNodes = (int *) calloc(V, sizeof(int));

    // Marcam nodurile principale
    allNodes[idxA] = 1;
    allNodes[idxB] = 1;

    // Marcam toti stramosii, vazuti ca toti parintii ai fiecarui parinte
    // pentru nodurile A si B
    markAllParents(G, allParents, allNodes, idxA);
    markAllParents(G, allParents, allNodes, idxB);

    for (int i = 0; i < V; i++)
    {
        if (obsNumbers[i])
        {   
            allNodes[i] = 1;
            markAllParents(G, allParents, allNodes, i);
        }
        
    }
    
    // Create a clone of the graph as we need it later, then treat multiple parents case
    TGraph clone = createAncestral(G, allParents, allNodes);
    clone = multipleParents(clone);

    //Convert to undirected graph, then delete de O1 ... On nodes
    TGraph undirected = convertToUndirected(clone);
    undirected = deleteObserved(undirected, obsNumbers);

    // Search for a path from A to B
    int *ok = (int *) calloc(1, sizeof(int));
    searchPath(undirected, idxA, idxB, ok);

    // Free all memory
    destroyGraph(clone);
    destroyGraph(undirected);
    if (obsNumbers != NULL)
    {
        free(obsNumbers);
    }
    
    free(allNodes);
    for (int i = 0; i < V; i++)
    {
        free(allParents[i]);
    }
    free(allParents);

    //Return result
    if ((*ok))
    {
        free(ok);
        return 1;
    }
    else
    {
        free(ok);
        return 0;
    }
}

void cerinta2(FILE *input, TGraph G, FILE *output)
{
    int k = 0;
    fscanf(input, "%d\n", &k);

    // The nodes we want to study
    char *A, *B;

    //Buffer of MAX_SIZE of a line
    char buffer[MAX_SIZE];
    
    for (int i = 0; i < k; i++)
    {
        fgets(buffer, MAX_SIZE, input);
        char *token = strtok(buffer, " ;|");
        A = (char *) calloc(strlen(token) + 1, sizeof(char));
        strcpy(A,token);

        token = strtok(NULL, " ;|");
        B = (char *) calloc(strlen(token) + 1, sizeof(char));
        strcpy(B,token);

        //List of observed nodes
        int lenObs = 0;
        char **observed;
        int maxSize = 5;

        token = strtok(NULL, " \n"); 
        if (token == NULL)
        {
            observed = NULL;
        }
        else
        {
            observed = (char **) calloc(maxSize, sizeof(char *));
        }
        
        while (token != NULL)
        {
            observed[lenObs] = (char *) calloc(strlen(token) + 1, sizeof(char));
            strcpy(observed[lenObs++], token);
            token = strtok(NULL, " \n"); 

            if (lenObs == maxSize)
            {
                maxSize = maxSize * 2;
                observed = (char **) realloc(observed, maxSize * sizeof(char *));
            }
            
        }
        observed = (char **) realloc(observed, lenObs * sizeof(char *));
        
        int ok = checkDependency(A, B, observed, lenObs, G);
        if (ok)
        {
            fprintf(output, "neindependente\n");
        }
        else
        {   
            fprintf(output, "independente\n");
        }
        
        free(A);
        free(B);
        for (int i = 0; i < lenObs; i++)
        {
            free(observed[i]);
        }
        free(observed);
    }
}

int main (int argc, char **argv) 
{
    FILE *input = fopen("bnet.in", "r");
    FILE *output = fopen("bnet.out","w");

    // Both tasks require the Graph
    TGraph G = getGraph(input);

    if (argc > 2)
    {
        printf("Too many arguments\n");
    }
    

    if (strcmp(argv[1], "-c1") == 0)
    {
        if (checkForCycles(G))
        {
            fprintf(output, "corect\n");
        }
        else
        {
            fprintf(output, "imposibil\n");
        }
    }

    if (strcmp(argv[1], "-c2") == 0)
    {
        cerinta2(input, G, output);
        
    }
    
    destroyGraph(G);
    fclose(input);
    fclose(output);

    return 0;
}