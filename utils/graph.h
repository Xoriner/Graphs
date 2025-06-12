#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdbool.h>

#define MAXV 1000

typedef struct {
    int start, end, weight;
} Edge;

typedef struct AdjNode {
    int vertex;
    int weight;
    struct AdjNode* next;
} AdjNode;

typedef struct {
    int vertices;
    int edges;
    int** matrix;
    Edge* edgeList;
    AdjNode** adjList;
    bool isDirected;
} Graph;

Graph* createGraph(int V, int E, bool isDirected);
void freeGraph(Graph* g);
Graph* loadGraphFromFile(const char* filename, bool isDirected);
Graph* generateRandomGraph(int V, float density); // For undirected graphs
Graph* generateRandomDirectedGraph(int V, float density); // For directed graphs
void printMatrix(Graph* g);
void buildAdjList(Graph* g);
void printAdjList(Graph* g);

#endif // GRAPH_H