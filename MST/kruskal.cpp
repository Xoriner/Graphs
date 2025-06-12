#include"kruskal.h"
// --- Disjoint-set (zbiory rozłączne) ---

int findSetGeneric(int* parent, int i) {
    if (parent[i] != i)
        parent[i] = findSetGeneric(parent, parent[i]);
    return parent[i];
}

void unionSetsGeneric(int* parent, int* rank, int x, int y) {
    int xroot = findSetGeneric(parent, x);
    int yroot = findSetGeneric(parent, y);
    if (rank[xroot] < rank[yroot])
        parent[xroot] = yroot;
    else if (rank[xroot] > rank[yroot])
        parent[yroot] = xroot;
    else {
        parent[yroot] = xroot;
        rank[xroot]++;
    }
}

// --- Kruskal dla macierzy sąsiedztwa ---

void kruskalMatrix(Graph* g) {
    auto start = std::chrono::high_resolution_clock::now();

    // Tworzenie listy krawędzi z macierzy
    Edge* edges = (Edge*)malloc(g->vertices * g->vertices * sizeof(Edge));
    int edgeCount = 0;

    for (int i = 0; i < g->vertices; i++) {
        for (int j = i + 1; j < g->vertices; j++) {
            if (g->matrix[i][j] != 0) {
                edges[edgeCount].start = i;
                edges[edgeCount].end = j;
                edges[edgeCount].weight = g->matrix[i][j];
                edgeCount++;
            }
        }
    }

    // Sortowanie bąbelkowe
    for (int i = 0; i < edgeCount - 1; i++) {
        for (int j = 0; j < edgeCount - i - 1; j++) {
            if (edges[j].weight > edges[j + 1].weight) {
                Edge tmp = edges[j];
                edges[j] = edges[j + 1];
                edges[j + 1] = tmp;
            }
        }
    }

    // Disjoint-set (dynamiczne)
    int* parent = (int*)malloc(g->vertices * sizeof(int));
    int* rank = (int*)calloc(g->vertices, sizeof(int));
    for (int i = 0; i < g->vertices; i++) parent[i] = i;

    int e = 0, i = 0, total = 0;
    printf("Kruskal (Matrix) MST edges:\n");
    while (e < g->vertices - 1 && i < edgeCount) {
        Edge next = edges[i++];
        int x = findSetGeneric(parent, next.start);
        int y = findSetGeneric(parent, next.end);
        if (x != y) {
            printf("%d - %d (%d)\n", next.start, next.end, next.weight);
            total += next.weight;
            unionSetsGeneric(parent, rank, x, y);
            e++;
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    printf("Total weight: %d\n", total);
    printf("Total time: %lld ms\n",
           std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());

    free(edges);
    free(parent);
    free(rank);
}

// --- Kruskal dla listy sąsiedztwa ---

void kruskalList(Graph* g) {
    auto start = std::chrono::high_resolution_clock::now();

    // Tworzenie listy krawędzi z listy sąsiedztwa
    Edge* edges = (Edge*)malloc(g->vertices * g->vertices * sizeof(Edge));
    int edgeCount = 0;

    for (int i = 0; i < g->vertices; i++) {
        AdjNode* curr = g->adjList[i];
        while (curr != NULL) {
            if (i < curr->vertex) { // unikamy duplikatów
                edges[edgeCount].start = i;
                edges[edgeCount].end = curr->vertex;
                edges[edgeCount].weight = curr->weight;
                edgeCount++;
            }
            curr = curr->next;
        }
    }

    // Sortowanie bąbelkowe
    for (int i = 0; i < edgeCount - 1; i++) {
        for (int j = 0; j < edgeCount - i - 1; j++) {
            if (edges[j].weight > edges[j + 1].weight) {
                Edge tmp = edges[j];
                edges[j] = edges[j + 1];
                edges[j + 1] = tmp;
            }
        }
    }

    int* parent = (int*)malloc(g->vertices * sizeof(int));
    int* rank = (int*)calloc(g->vertices, sizeof(int));
    for (int i = 0; i < g->vertices; i++) parent[i] = i;

    int total = 0, e = 0;
    printf("Kruskal (List) MST edges:\n");
    for (int i = 0; i < edgeCount && e < g->vertices - 1; i++) {
        Edge next = edges[i];
        int x = findSetGeneric(parent, next.start);
        int y = findSetGeneric(parent, next.end);
        if (x != y) {
            printf("%d - %d (%d)\n", next.start, next.end, next.weight);
            total += next.weight;
            unionSetsGeneric(parent, rank, x, y);
            e++;
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    printf("Total weight: %d\n", total);
    printf("Total time: %lld ms\n",
           std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());

    free(parent);
    free(rank);
    free(edges);
}