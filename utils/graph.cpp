#include "graph.h"
#include <stdlib.h>

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