#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

#define MAXV 1000

typedef struct {
    int start, end, weight;
} Edge;

typedef struct {
    int vertices;
    int edges;
    int** matrix;
    Edge* edgeList;
} Graph;

int minKey(int key[], int mstSet[], int V) {
    int min = INT_MAX, min_index = -1;
    for (int v = 0; v < V; v++)
        if (mstSet[v] == 0 && key[v] < min)
            min = key[v], min_index = v;
    return min_index;
}

void primMatrix(Graph* g) {
    int V = g->vertices;
    int parent[V];
    int key[V];
    int mstSet[V];

    for (int i = 0; i < V; i++)
        key[i] = INT_MAX, mstSet[i] = 0;

    key[0] = 0;
    parent[0] = -1;

    for (int count = 0; count < V - 1; count++) {
        int u = minKey(key, mstSet, V);
        mstSet[u] = 1;
        for (int v = 0; v < V; v++)
            if (g->matrix[u][v] && mstSet[v] == 0 && g->matrix[u][v] < key[v])
                parent[v] = u, key[v] = g->matrix[u][v];
    }

    int total = 0;
    printf("Prim (Matrix) MST edges:\n");
    for (int i = 1; i < V; i++) {
        printf("%d - %d (%d)\n", parent[i], i, g->matrix[i][parent[i]]);
        total += g->matrix[i][parent[i]];
    }
    printf("Total weight: %d\n", total);
}

// Disjoint-set for Kruskal
int parent[MAXV], rank[MAXV];

int findSet(int i) {
    if (parent[i] != i)
        parent[i] = findSet(parent[i]);
    return parent[i];
}

void unionSets(int x, int y) {
    int xroot = findSet(x);
    int yroot = findSet(y);
    if (rank[xroot] < rank[yroot])
        parent[xroot] = yroot;
    else if (rank[xroot] > rank[yroot])
        parent[yroot] = xroot;
    else {
        parent[yroot] = xroot;
        rank[xroot]++;
    }
}

void kruskal(Graph* g) {
    // Simple bubble sort (you can optimize)
    for (int i = 0; i < g->edges - 1; i++) {
        for (int j = 0; j < g->edges - i - 1; j++) {
            if (g->edgeList[j].weight > g->edgeList[j + 1].weight) {
                Edge tmp = g->edgeList[j];
                g->edgeList[j] = g->edgeList[j + 1];
                g->edgeList[j + 1] = tmp;
            }
        }
    }

    for (int v = 0; v < g->vertices; v++) {
        parent[v] = v;
        rank[v] = 0;
    }

    printf("Kruskal MST edges:\n");
    int e = 0, i = 0, total = 0;
    while (e < g->vertices - 1 && i < g->edges) {
        Edge next = g->edgeList[i++];
        int x = findSet(next.start);
        int y = findSet(next.end);
        if (x != y) {
            printf("%d - %d (%d)\n", next.start, next.end, next.weight);
            total += next.weight;
            unionSets(x, y);
            e++;
        }
    }
    printf("Total weight: %d\n", total);
}

// Memory functions
Graph* createGraph(int V, int E) {
    Graph* g = (Graph*)malloc(sizeof(Graph));
    g->vertices = V;
    g->edges = E;
    g->edgeList = (Edge*)malloc(sizeof(Edge) * E);

    g->matrix = (int**)malloc(V * sizeof(int*));
    for (int i = 0; i < V; i++) {
        g->matrix[i] = (int*)calloc(V, sizeof(int));
    }
    return g;
}

void freeGraph(Graph* g) {
    for (int i = 0; i < g->vertices; i++) {
        free(g->matrix[i]);
    }
    free(g->matrix);
    free(g->edgeList);
    free(g);
}

// Sample loader
Graph* loadGraphFromFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) return NULL;
    int E, V;
    fscanf(file, "%d %d", &E, &V);
    Graph* g = createGraph(V, E);
    for (int i = 0; i < E; i++) {
        int u, v, w;
        fscanf(file, "%d %d %d", &u, &v, &w);
        g->matrix[u][v] = w;
        g->matrix[v][u] = w;
        g->edgeList[i].start = u;
        g->edgeList[i].end = v;
        g->edgeList[i].weight = w;
    }
    fclose(file);
    return g;
}

void printMatrix(Graph* g) {
    printf("Adjacency Matrix:\n");
    for (int i = 0; i < g->vertices; i++) {
        for (int j = 0; j < g->vertices; j++) {
            printf("%3d ", g->matrix[i][j]);
        }
        printf("\n");
    }
}

// === MENU ===

int main() {
    Graph* g = NULL;
    int choice;
    char filename[256];

    while (1) {
        printf("\n== MST Menu ==\n");
        printf("1. Load graph from file\n");
        printf("2. Display matrix\n");
        printf("3. Prim (Matrix)\n");
        printf("4. Kruskal\n");
        printf("5. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Filename: ");
                scanf("%s", filename);
                if (g) freeGraph(g);
                g = loadGraphFromFile(filename);
                if (g) printf("Graph loaded.\n");
                else printf("Failed to load graph.\n");
                break;
            case 2:
                if (g) printMatrix(g);
                else printf("Load a graph first.\n");
                break;
            case 3:
                if (g) primMatrix(g);
                else printf("Load a graph first.\n");
                break;
            case 4:
                if (g) kruskal(g);
                else printf("Load a graph first.\n");
                break;
            case 5:
                if (g) freeGraph(g);
                return 0;
        }
    }
}
