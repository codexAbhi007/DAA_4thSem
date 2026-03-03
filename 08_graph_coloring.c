#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct AdjNode
{
    int v;
    struct AdjNode *next;
};

struct AdjNode *createNode(int v);
void addEdge(struct AdjNode **graph, int u, int v);
void displayGraph(struct AdjNode **graph, int V);

void mcoloring(struct AdjNode **graph, char x[], int V, int k, char colors[],int c);

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
    printf("Enter edges (u v):\n");
    for (int i = 0; i < E; i++)
    {
        int u, v;
        scanf("%d %d", &u, &v);
        addEdge(graph, u, v);
    }
    int c;
    c = 3;
    char colors[c];

    colors[0] = 'R';
    colors[1] = 'G';
    colors[2] = 'B';

    char x[V + 1];
    for (int i = 0; i <= V; i++)
    {
        x[i] = '\0';
    }
    displayGraph(graph,V);
    mcoloring(graph, x, V, 1, colors,c);

    return 0;
}

struct AdjNode *createNode(int v)
{
    struct AdjNode *newNode = (struct AdjNode *)malloc(sizeof(struct AdjNode));
    newNode->v = v;
    newNode->next = NULL;
    return newNode;
}

void addEdge(struct AdjNode **graph, int u, int v)
{
    struct AdjNode *node = createNode(v);
    node->next = graph[u];
    graph[u] = node;

    node = createNode(u);
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
            printf("-> (v: %d) ", temp->v);
            temp = temp->next;
        }
        printf("\n");
    }
}

void mcoloring(struct AdjNode **graph, char x[], int V, int k, char colors[],int c)
{
    if (k > V)
    {
        for(int i =1 ; i <= V; ++i){
            printf("Vertex %d -> %c\n",i,x[i]);
        }
        printf("\n");
        return;
    }
    for (int i = 0; i < c; ++i){
        x[k] = colors[i];
        struct AdjNode *temp = graph[k];
        while(temp != NULL){
            if(x[temp->v] != x[k]){
                mcoloring(graph,x,V,k+1,colors,c);
            }
            temp = temp -> next;
        }
        x[k] = '\0';

    }
}

// Helper function to check coloring possibility
int canColor(struct AdjNode **graph, int V, int k, int c, int x[])
{
    if (k > V)
        return 1;

    for (int color = 1; color <= c; color++)
    {
        x[k] = color;

        int safe = 1;
        struct AdjNode *temp = graph[k];

        while (temp != NULL)
        {
            if (x[temp->v] == x[k])
            {
                safe = 0;
                break;
            }
            temp = temp->next;
        }

        if (safe && canColor(graph, V, k + 1, c, x))
            return 1;
    }

    x[k] = 0;
    return 0;
}


// Main chromatic number function
int chromaticNumber(struct AdjNode **graph, int V)
{
    int x[V + 1];

    for (int c = 1; c <= V; c++)
    {
        for (int i = 1; i <= V; i++)
            x[i] = 0;

        if (canColor(graph, V, 1, c, x))
            return c;
    }

    return V;
}