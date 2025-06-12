#include "dijkstra.h"
#include <stdio.h>
#include <chrono>
#include <stdlib.h>

// ==================== Dijkstra: Matrix ====================
void dijkstraMatrix(Graph* g, int start) {
    auto t0 = std::chrono::high_resolution_clock::now();
    int V = g->vertices;
    int* dist = (int*)malloc(V * sizeof(int));
    bool* visited = (bool*)calloc(V, sizeof(bool));

    for (int i = 0; i < V; i++) dist[i] = INT_MAX;
    dist[start] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = -1, min = INT_MAX;
        for (int v = 0; v < V; v++)
            if (!visited[v] && dist[v] < min)
                min = dist[v], u = v;
        if (u == -1) break;
        visited[u] = true;

        for (int v = 0; v < V; v++)
            if (g->matrix[u][v] && !visited[v] && dist[u] + g->matrix[u][v] < dist[v])
                dist[v] = dist[u] + g->matrix[u][v];
    }

    printf("Dijkstra (Matrix) from %d:\n", start);
    for (int i = 0; i < V; i++)
        printf("%d -> %d: %d\n", start, i, dist[i]);

    auto t1 = std::chrono::high_resolution_clock::now();
    printf("Time: %lld ms\n", std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count());
    free(dist);
    free(visited);
}

// ==================== Dijkstra: List ====================
void dijkstraList(Graph* g, int start) {
    auto t0 = std::chrono::high_resolution_clock::now();
    int V = g->vertices;
    int* dist = (int*)malloc(V * sizeof(int));
    bool* visited = (bool*)calloc(V, sizeof(bool));

    for (int i = 0; i < V; i++) dist[i] = INT_MAX;
    dist[start] = 0;

    for (int count = 0; count < V; count++) {
        int u = -1, min = INT_MAX;
        for (int v = 0; v < V; v++)
            if (!visited[v] && dist[v] < min)
                min = dist[v], u = v;
        if (u == -1) break;
        visited[u] = true;

        AdjNode* curr = g->adjList[u];
        while (curr) {
            int v = curr->vertex;
            if (!visited[v] && dist[u] + curr->weight < dist[v])
                dist[v] = dist[u] + curr->weight;
            curr = curr->next;
        }
    }

    printf("Dijkstra (List) from %d:\n", start);
    for (int i = 0; i < V; i++)
        printf("%d -> %d: %d\n", start, i, dist[i]);

    auto t1 = std::chrono::high_resolution_clock::now();
    printf("Time: %lld ms\n", std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count());
    free(dist);
    free(visited);
}