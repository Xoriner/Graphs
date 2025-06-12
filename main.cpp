#include "utils/graph.h"
#include "MST/prim.h"
#include "MST/kruskal.h"
#include <stdio.h>

int main() {
    Graph* g = NULL;
    int choice;
    char filename[256];

    while (1) {
        printf("\n== MST Menu ==\n");
        printf("1. Load graph from file\n");
        printf("2. Display matrix\n");
        printf("3. Prim (Matrix)\n");
        printf("4. Kruskal\n");
        printf("5. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Filename: ");
            scanf("%s", filename);
            if (g) freeGraph(g);
            g = loadGraphFromFile(filename);
            if (g) printf("Graph loaded.\n");
            else printf("Failed to load graph.\n");
            break;
            case 2:
                if (g) printMatrix(g);
                else printf("Load a graph first.\n");
            break;
            case 3:
                if (g) primMatrix(g);
                else printf("Load a graph first.\n");
            break;
            case 4:
                if (g) kruskal(g);
                else printf("Load a graph first.\n");
            break;
            case 5:
                if (g) freeGraph(g);
            return 0;
        }
    }
}
