#include "kruskal.h"
#include <stdio.h>
#include <chrono>

static int parent[MAXV], rank[MAXV];

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
    auto start = std::chrono::high_resolution_clock::now();

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

    auto end = std::chrono::high_resolution_clock::now();
    printf("Total weight: %d\n", total);
    printf("Total time: %lld ms\n",
        std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());
}
