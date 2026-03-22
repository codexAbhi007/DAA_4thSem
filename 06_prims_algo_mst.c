#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct AdjNode
{
    int v;
    int weight;
    struct AdjNode *next;
};


struct AdjNode *createNode(int dest, int weight);
void addEdge(struct AdjNode **graph, int u, int v, int w);
void displayGraph(struct AdjNode **graph, int V);
int primMST(struct AdjNode **graph, int V, int startingVertex);
void shiftDown(int heap[], int key[], int map[], int heapSize, int i);
void swap(int heap[], int map[], int i, int j);
int extractMin(int heap[], int key[], int map[], int *size);
void shiftUp(int heap[], int key[], int map[], int i);

int main()
{
    int V, E;

    printf("Enter number of vertices: ");
    scanf("%d", &V);

    printf("Enter number of edges: ");
    scanf("%d", &E);

    struct AdjNode **graph = (struct AdjNode **)malloc((V + 1) * sizeof(struct AdjNode *));
    for (int i = 0; i <= V; i++)
    {
        graph[i] = NULL;
    }
    printf("Enter edges (u v w):\n");
    for (int i = 0; i < E; i++)
    {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        addEdge(graph, u, v, w);
    }

    displayGraph(graph, V);

    int startingVertex;
    printf("Enter starting vertex: ");
    scanf("%d", &startingVertex);
    printf("\n");
    int minCost = primMST(graph, V, startingVertex);
    printf("Minimum cost of MST: %d\n", minCost);

    return 0;
}

struct AdjNode *createNode(int v, int w)
{
    struct AdjNode *newNode = (struct AdjNode *)malloc(sizeof(struct AdjNode));
    newNode->v = v;
    newNode->weight = w;
    newNode->next = NULL;
    return newNode;
}

void addEdge(struct AdjNode **graph, int u, int v, int w)
{
    struct AdjNode *node = createNode(v, w);
    node->next = graph[u];
    graph[u] = node;

    node = createNode(u, w);
    node->next = graph[v];
    graph[v] = node;
}

void displayGraph(struct AdjNode **graph, int V)
{
    for (int i = 1; i <= V; i++)
    {
        struct AdjNode *temp = graph[i];
        printf("Vertex %d: ", i);
        while (temp)
        {
            printf("-> (v: %d, w: %d) ", temp->v, temp->weight);
            temp = temp->next;
        }
        printf("\n");
    }
}

void swap(int heap[], int map[], int i, int j)
{
    int temp = heap[i];
    heap[i] = heap[j];
    heap[j] = temp;

    map[heap[i]] = i;
    map[heap[j]] = j;
}

void shiftDown(int heap[], int key[], int map[], int heapSize, int i)
{
    int p = i;
    int lc = 2 * i + 1;
    int rc = 2 * i + 2;

    if (lc < heapSize && key[heap[lc]] < key[heap[p]]) p = lc;
    if (rc < heapSize && key[heap[rc]] < key[heap[p]]) p = rc;
    
    if (p == i) return;

    swap(heap, map, i, p);
    shiftDown(heap, key, map, heapSize, p);
}

int extractMin(int heap[], int key[], int map[], int *size)
{
    int root = heap[0];
    heap[0] = heap[(*size) - 1];
    map[heap[0]] = 0;
    map[root] = -1;
    (*size)--;

    shiftDown(heap, key, map, *size, 0);
    return root;
}

void shiftUp(int heap[], int key[], int map[], int i)
{
    int p = (i - 1) / 2;
    while (i > 0 && key[heap[i]] < key[heap[p]])
    {
        swap(heap, map, i, p);
        i = p;
        p = (i - 1) / 2;
    }
}

int primMST(struct AdjNode **graph, int V, int startingVertex)
{
    int minCost = 0;

    int parent[V + 1];
    int key[V + 1];
    int inMST[V + 1];
    int heap[V];
    int map[V + 1];
    int heapSize = V;

    // initialisation
    for (int i = 1; i <= V; ++i)
    {
        key[i] = INT_MAX;
        parent[i] = -1;
        inMST[i] = 0;
        heap[i - 1] = i;
        map[i] = i - 1;
    }

    key[startingVertex] = 0;
    for (int i = (heapSize / 2) - 1; i >= 0; i--)
    {
        // heapify
        shiftDown(heap, key, map, heapSize, i);
    }

    while (heapSize > 0)
    {
        int u = extractMin(heap, key, map, &heapSize);
        if (parent[u] != -1)
        {
            printf("%d - %d \t%d\n", parent[u], u, key[u]);
            minCost += key[u];
        }
        inMST[u] = 1;

        struct AdjNode *temp = graph[u];
        while (temp)
        {
            int v = temp->v;
            int w = temp->weight;

            if (inMST[v] == 0 && w < key[v])
            {
                parent[v] = u;
                key[v] = w;
                shiftUp(heap, key, map, map[v]);
            }
            temp = temp->next;
        }
    }

    return minCost;
}
