#ifndef PRIM_H
#define PRIM_H

#include "../utils/graph.h"
#include <limits.h>
#include <stdio.h>
#include <chrono>
#include <stdlib.h>

// Prototypy funkcji
void primMatrix(Graph* g);
void primList(Graph* g);

// Struktury dla kopca (używane tylko w primList)
typedef struct {
    int vertex;
    int key;
} HeapNode;

typedef struct {
    HeapNode* nodes;    // Tablica węzłów kopca
    int* pos;           // Pozycje wierzchołków w kopcu
    int size;           // Aktualny rozmiar kopca
    int capacity;       // Maksymalna pojemność kopca
} MinHeap;

// Funkcje pomocnicze dla kopca
MinHeap* createMinHeap(int capacity);
void freeMinHeap(MinHeap* heap);
HeapNode extractMin(MinHeap* heap);
void decreaseKey(MinHeap* heap, int vertex, int key);
bool isInHeap(MinHeap* heap, int vertex);

#endif // PRIM_H