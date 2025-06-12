#include "bellmanford.h"
#include <stdio.h>
#include <chrono>
#include <stdlib.h>

// ==================== Bellman-Ford: Matrix ====================
void bellmanFordMatrix(Graph* g, int start) {
    auto t0 = std::chrono::high_resolution_clock::now();
    int V = g->vertices;
    int* dist = (int*)malloc(V * sizeof(int));
    for (int i = 0; i < V; i++) dist[i] = INT_MAX;
    dist[start] = 0;

    for (int i = 1; i < V; i++) {
        for (int u = 0; u < V; u++) {
            for (int v = 0; v < V; v++) {
                if (g->matrix[u][v] && dist[u] != INT_MAX && dist[u] + g->matrix[u][v] < dist[v])
                    dist[v] = dist[u] + g->matrix[u][v];
            }
        }
    }

    printf("Bellman-Ford (Matrix) from %d:\n", start);
    for (int i = 0; i < V; i++)
        printf("%d -> %d: %d\n", start, i, dist[i]);

    auto t1 = std::chrono::high_resolution_clock::now();
    printf("Time: %lld ms\n", std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count());
    free(dist);
}

// ==================== Bellman-Ford: List ====================
void bellmanFordList(Graph* g, int start) {
    auto t0 = std::chrono::high_resolution_clock::now();
    int V = g->vertices;
    int* dist = (int*)malloc(V * sizeof(int));
    for (int i = 0; i < V; i++) dist[i] = INT_MAX;
    dist[start] = 0;

    for (int i = 1; i < V; i++) {
        for (int u = 0; u < V; u++) {
            AdjNode* curr = g->adjList[u];
            while (curr) {
                int v = curr->vertex;
                if (dist[u] != INT_MAX && dist[u] + curr->weight < dist[v])
                    dist[v] = dist[u] + curr->weight;
                curr = curr->next;
            }
        }
    }

    printf("Bellman-Ford (List) from %d:\n", start);
    for (int i = 0; i < V; i++)
        printf("%d -> %d: %d\n", start, i, dist[i]);

    auto t1 = std::chrono::high_resolution_clock::now();
    printf("Time: %lld ms\n", std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count());
    free(dist);
}