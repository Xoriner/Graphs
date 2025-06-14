#include "prim.h"

// ==================== MST: Prim (Matrix) ====================

int minKey(int key[], bool mstSet[], int V) {
    int min = INT_MAX, min_index = -1;
    for (int v = 0; v < V; v++) {
        if (!mstSet[v] && key[v] < min) {
            min = key[v];
            min_index = v;
        }
    }
    return min_index;
}

void primMatrix(Graph* g) {
    auto start = std::chrono::high_resolution_clock::now();
    int V = g->vertices;

    int* parent = (int*)malloc(V * sizeof(int));
    int* key = (int*)malloc(V * sizeof(int));
    bool* mstSet = (bool*)malloc(V * sizeof(bool));

    for (int i = 0; i < V; i++) {
        key[i] = INT_MAX;
        mstSet[i] = false;
    }

    key[0] = 0;
    parent[0] = -1;

    for (int count = 0; count < V - 1; count++) {
        int u = minKey(key, mstSet, V);
        mstSet[u] = true;

        for (int v = 0; v < V; v++) {
            if (g->matrix[u][v] && !mstSet[v] && g->matrix[u][v] < key[v]) {
                parent[v] = u;
                key[v] = g->matrix[u][v];
            }
        }
    }

    auto end = std::chrono::high_resolution_clock::now();

    int total = 0;
    printf("Prim (Matrix) MST edges:\n");
    for (int i = 1; i < V; i++) {
        if (parent[i] != -1) {
            printf("%d - %d (%d)\n", parent[i], i, g->matrix[i][parent[i]]);
            total += g->matrix[i][parent[i]];
        }
    }
    printf("Total weight: %d\n", total);
    printf("Total time: %lld ms\n",
           std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());

    free(parent);
    free(key);
    free(mstSet);
}

// ==================== MST: Prim (List) ====================

MinHeap* createMinHeap(int capacity) {
    MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
    heap->nodes = (HeapNode*)malloc(capacity * sizeof(HeapNode));
    heap->pos = (int*)malloc(capacity * sizeof(int));
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

void freeMinHeap(MinHeap* heap) {
    if (heap) {
        free(heap->nodes);
        free(heap->pos);
        free(heap);
    }
}

void heapify(MinHeap* heap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < heap->size && heap->nodes[left].key < heap->nodes[smallest].key) {
        smallest = left;
    }
    if (right < heap->size && heap->nodes[right].key < heap->nodes[smallest].key) {
        smallest = right;
    }

    if (smallest != idx) {
        HeapNode temp = heap->nodes[idx];
        heap->nodes[idx] = heap->nodes[smallest];
        heap->nodes[smallest] = temp;

        heap->pos[heap->nodes[idx].vertex] = idx;
        heap->pos[heap->nodes[smallest].vertex] = smallest;

        heapify(heap, smallest);
    }
}

HeapNode extractMin(MinHeap* heap) {
    HeapNode root = heap->nodes[0];
    heap->nodes[0] = heap->nodes[--heap->size];
    heap->pos[heap->nodes[0].vertex] = 0;
    heapify(heap, 0);
    return root;
}

void decreaseKey(MinHeap* heap, int vertex, int key) {
    int i = heap->pos[vertex];
    if (key > heap->nodes[i].key) return;

    heap->nodes[i].key = key;
    while (i > 0 && heap->nodes[i].key < heap->nodes[(i - 1) / 2].key) {
        heap->pos[heap->nodes[i].vertex] = (i - 1) / 2;
        heap->pos[heap->nodes[(i - 1) / 2].vertex] = i;
        HeapNode temp = heap->nodes[i];
        heap->nodes[i] = heap->nodes[(i - 1) / 2];
        heap->nodes[(i - 1) / 2] = temp;
        i = (i - 1) / 2;
    }
}

bool isInHeap(MinHeap* heap, int vertex) {
    return heap->pos[vertex] < heap->size;
}

void primList(Graph* g) {
    auto start = std::chrono::high_resolution_clock::now();
    int V = g->vertices;

    int* parent = (int*)malloc(V * sizeof(int));
    int* key = (int*)malloc(V * sizeof(int));
    bool* inHeap = (bool*)malloc(V * sizeof(bool));
    MinHeap* heap = createMinHeap(V);

    for (int v = 0; v < V; v++) {
        parent[v] = -1;
        key[v] = INT_MAX;
        inHeap[v] = true;
    }

    key[0] = 0;

    for (int v = 0; v < V; v++) {
        heap->nodes[v].vertex = v;
        heap->nodes[v].key = key[v];
        heap->pos[v] = v;
    }
    heap->size = V;

    while (heap->size > 0) {
        HeapNode minNode = extractMin(heap);
        int u = minNode.vertex;
        inHeap[u] = false;

        AdjNode* curr = g->adjList[u];
        while (curr != NULL) {
            int v = curr->vertex;
            int weight = curr->weight;

            if (inHeap[v] && weight < key[v]) {
                key[v] = weight;
                parent[v] = u;
                decreaseKey(heap, v, weight);
            }
            curr = curr->next;
        }
    }

    auto end = std::chrono::high_resolution_clock::now();

    int total = 0;
    printf("Prim (List) MST edges:\n");
    for (int i = 1; i < V; i++) {
        if (parent[i] != -1) {
            printf("%d - %d (%d)\n", parent[i], i, key[i]);
            total += key[i];
        }
    }
    printf("Total weight: %d\n", total);
    printf("Total time: %lld ms\n",
           std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());

    free(parent);
    free(key);
    free(inHeap);
    freeMinHeap(heap);
}
