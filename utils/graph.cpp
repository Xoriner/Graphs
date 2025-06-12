#include "graph.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

Graph* createGraph(int V, int E, bool isDirected) {
    Graph* g = (Graph*)malloc(sizeof(Graph));
    g->vertices = V;
    g->edges = E;
    g->isDirected = isDirected;
    g->edgeList = (Edge*)malloc(sizeof(Edge) * E);

    g->matrix = (int**)malloc(V * sizeof(int*));
    for (int i = 0; i < V; i++) {
        g->matrix[i] = (int*)calloc(V, sizeof(int));
    }

    g->adjList = (AdjNode**)malloc(V * sizeof(AdjNode*));
    for (int i = 0; i < V; i++) {
        g->adjList[i] = NULL;
    }

    return g;
}

void freeGraph(Graph* g) {
    for (int i = 0; i < g->vertices; i++) {
        free(g->matrix[i]);
        AdjNode* curr = g->adjList[i];
        while (curr) {
            AdjNode* tmp = curr;
            curr = curr->next;
            free(tmp);
        }
    }
    free(g->matrix);
    free(g->adjList);
    free(g->edgeList);
    free(g);
}

Graph* loadGraphFromFile(const char* filename, bool isDirected) {
    FILE* file = fopen(filename, "r");
    if (!file) return NULL;

    int E, V;
    fscanf(file, "%d %d", &E, &V);

    Graph* g = createGraph(V, E, isDirected);

    for (int i = 0; i < E; i++) {
        int u, v, w;
        fscanf(file, "%d %d %d", &u, &v, &w);

        g->matrix[u][v] = w;
        g->edgeList[i].start = u;
        g->edgeList[i].end = v;
        g->edgeList[i].weight = w;

        if (!isDirected) {
            g->matrix[v][u] = w;
        }
    }

    fclose(file);
    buildAdjList(g);
    return g;
}

void buildAdjList(Graph* g) {
    for (int i = 0; i < g->edges; i++) {
        int u = g->edgeList[i].start;
        int v = g->edgeList[i].end;
        int w = g->edgeList[i].weight;

        AdjNode* newNode = (AdjNode*)malloc(sizeof(AdjNode));
        newNode->vertex = v;
        newNode->weight = w;
        newNode->next = g->adjList[u];
        g->adjList[u] = newNode;

        if (!g->isDirected) {
            newNode = (AdjNode*)malloc(sizeof(AdjNode));
            newNode->vertex = u;
            newNode->weight = w;
            newNode->next = g->adjList[v];
            g->adjList[v] = newNode;
        }
    }
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

void printAdjList(Graph* g) {
    printf("Adjacency List:\n");
    for (int i = 0; i < g->vertices; i++) {
        printf("%d:", i);
        AdjNode* curr = g->adjList[i];
        while (curr) {
            printf(" -> %d(%d)", curr->vertex, curr->weight);
            curr = curr->next;
        }
        printf("\n");
    }
}

Graph* generateRandomGraph(int V, float density) {
    int maxEdges = V * (V - 1) / 2;
    int targetEdges = (int)(density * maxEdges);

    Graph* g = createGraph(V, targetEdges + V - 1, false); // allocate extra space for MST part
    int edgeIndex = 0;

    int** added = (int**)malloc(V * sizeof(int*));
    for (int i = 0; i < V; i++) {
        added[i] = (int*)calloc(V, sizeof(int));
    }

    srand((unsigned int)time(NULL));

    // Generate a connected spanning tree
    for (int i = 1; i < V; i++) {
        int v = rand() % i;
        int u = i;
        int w = rand() % 100 + 1;

        g->matrix[u][v] = g->matrix[v][u] = w;

        g->edgeList[edgeIndex].start = u;
        g->edgeList[edgeIndex].end = v;
        g->edgeList[edgeIndex].weight = w;

        added[u][v] = added[v][u] = 1;
        edgeIndex++;
    }

    // Add additional edges to reach desired density
    while (edgeIndex < targetEdges) {
        int u = rand() % V;
        int v = rand() % V;
        if (u != v && !added[u][v]) {
            int w = rand() % 100 + 1;

            g->matrix[u][v] = g->matrix[v][u] = w;

            g->edgeList[edgeIndex].start = u;
            g->edgeList[edgeIndex].end = v;
            g->edgeList[edgeIndex].weight = w;

            added[u][v] = added[v][u] = 1;
            edgeIndex++;
        }
    }

    g->edges = edgeIndex;

    for (int i = 0; i < V; i++) {
        free(added[i]);
    }
    free(added);

    buildAdjList(g);
    return g;
}

Graph* generateRandomDirectedGraph(int V, float density) {
    int maxEdges = V * (V - 1);
    int targetEdges = (int)(density * maxEdges);

    Graph* g = createGraph(V, targetEdges + V, true); // +V for the cycle to ensure connectivity
    int edgeIndex = 0;

    int** added = (int**)malloc(V * sizeof(int*));
    for (int i = 0; i < V; i++) {
        added[i] = (int*)calloc(V, sizeof(int));
    }

    srand((unsigned int)time(NULL));

    // Create a cycle through all vertices to ensure connectivity
    for (int i = 0; i < V; i++) {
        int u = i;
        int v = (i + 1) % V;
        int w = rand() % 100 + 1;

        g->matrix[u][v] = w;
        g->edgeList[edgeIndex].start = u;
        g->edgeList[edgeIndex].end = v;
        g->edgeList[edgeIndex].weight = w;
        added[u][v] = 1;
        edgeIndex++;
    }

    // Add additional edges to reach desired density
    while (edgeIndex < targetEdges) {
        int u = rand() % V;
        int v = rand() % V;
        if (u != v && !added[u][v]) {
            int w = rand() % 100 + 1;

            g->matrix[u][v] = w;
            g->edgeList[edgeIndex].start = u;
            g->edgeList[edgeIndex].end = v;
            g->edgeList[edgeIndex].weight = w;
            added[u][v] = 1;
            edgeIndex++;
        }
    }

    g->edges = edgeIndex;

    for (int i = 0; i < V; i++) {
        free(added[i]);
    }
    free(added);

    buildAdjList(g);
    return g;
}
