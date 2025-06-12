#include "prim.h"
#include <limits.h>
#include <stdio.h>
#include <chrono>

int minKey(int key[], int mstSet[], int V) {
    int min = INT_MAX, min_index = -1;
    for (int v = 0; v < V; v++)
        if (!mstSet[v] && key[v] < min)
            min = key[v], min_index = v;
    return min_index;
}

void primMatrix(Graph* g) {
    auto start = std::chrono::high_resolution_clock::now();
    int V = g->vertices;
    int parent[V], key[V], mstSet[V];

    for (int i = 0; i < V; i++)
        key[i] = INT_MAX, mstSet[i] = 0;

    key[0] = 0;
    parent[0] = -1;

    for (int count = 0; count < V - 1; count++) {
        int u = minKey(key, mstSet, V);
        mstSet[u] = 1;
        for (int v = 0; v < V; v++)
            if (g->matrix[u][v] && !mstSet[v] && g->matrix[u][v] < key[v])
                parent[v] = u, key[v] = g->matrix[u][v];
    }

    int total = 0;
    printf("Prim (Matrix) MST edges:\n");
    for (int i = 1; i < V; i++) {
        printf("%d - %d (%d)\n", parent[i], i, g->matrix[i][parent[i]]);
        total += g->matrix[i][parent[i]];
    }
    auto end = std::chrono::high_resolution_clock::now();
    printf("Total weight: %d\n", total);
    printf("Total time: %lld ms\n",
        std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());
}
