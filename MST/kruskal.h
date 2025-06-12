#ifndef KRUSKAL_H
#define KRUSKAL_H

#include "../utils/graph.h"
#include <stdio.h>
#include <chrono>
#include <stdlib.h>

int findSetGeneric(int* parent, int i);
void unionSetsGeneric(int* parent, int* rank, int x, int y);
void kruskalMatrix(Graph* g);
void kruskalList(Graph* g);

#endif // KRUSKAL_H