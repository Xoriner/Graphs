#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>

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

Graph* createGraph(int V, int E);
void freeGraph(Graph* g);
Graph* loadGraphFromFile(const char* filename);
void printMatrix(Graph* g);

#endif // GRAPH_H