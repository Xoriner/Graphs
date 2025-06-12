#include "utils/graph.h"
#include "MST/prim.h"
#include "MST/kruskal.h"
#include "Path/bellmanford.h"
#include "Path/dijkstra.h"
#include <stdio.h>

int main() {
    Graph* g = NULL;
    int choice;
    char filename[256];
    int vertices, startVertex;
    float density;

    while (1) {
        printf("\n== Main Menu ==\n");
        printf("1. Load graph from file\n");
        printf("2. Generate random graph\n");
        printf("3. Display matrix\n");
        printf("4. Display list\n");
        printf("5. MST - Prim (Matrix)\n");
        printf("6. MST - Prim (List)\n");
        printf("7. MST - Kruskal (Matrix)\n");
        printf("8. MST - Kruskal (List)\n");
        printf("9. SP - Dijkstra (Matrix)\n");
        printf("10. SP - Dijkstra (List)\n");
        printf("11. SP - Bellman-Ford (Matrix)\n");
        printf("12. SP - Bellman-Ford (List)\n");
        printf("13. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Filename: ");
                scanf("%s", filename);
                if (g) freeGraph(g);
                g = loadGraphFromFile(filename, true);
                if (g) {
                    printf("Graph loaded.\n");
                    //printMatrix(g);
                    //printAdjList(g);
                } else {
                    printf("Failed to load graph.\n");
                }
                break;

            case 2:
                printf("Number of vertices: ");
                scanf("%d", &vertices);
                printf("Density (0.2 = 20%%): ");
                scanf("%f", &density);
                if (g) freeGraph(g);
                g = generateRandomGraph(vertices, density);
                printf("Random graph generated.\n");
                //printMatrix(g);
                //printAdjList(g);
                break;

            case 3:
                if (g) printMatrix(g);
                else printf("Load or generate a graph first.\n");
                break;

            case 4:
                if (g) printAdjList(g);
                else printf("Load or generate a graph first.\n");
                break;

            case 5:
                if (g) primMatrix(g);
                else printf("Load or generate a graph first.\n");
                break;

            case 6:
                if (g) primList(g);
                else printf("Load or generate a graph first.\n");
                break;

            case 7:
                if (g) kruskalMatrix(g);
                else printf("Load or generate a graph first.\n");
                break;

            case 8:
                if (g) kruskalList(g);
                else printf("Load or generate a graph first.\n");
                break;

            case 9:
                if (g) {
                    printf("Start vertex: ");
                    scanf("%d", &startVertex);
                    dijkstraMatrix(g, startVertex);
                } else {
                    printf("Load or generate a graph first.\n");
                }
                break;

            case 10:
                if (g) {
                    printf("Start vertex: ");
                    scanf("%d", &startVertex);
                    dijkstraList(g, startVertex);
                } else {
                    printf("Load or generate a graph first.\n");
                }
                break;

            case 11:
                if (g) {
                    printf("Start vertex: ");
                    scanf("%d", &startVertex);
                    bellmanFordMatrix(g, startVertex);
                } else {
                    printf("Load or generate a graph first.\n");
                }
                break;

            case 12:
                if (g) {
                    printf("Start vertex: ");
                    scanf("%d", &startVertex);
                    bellmanFordList(g, startVertex);
                } else {
                    printf("Load or generate a graph first.\n");
                }
                break;

            case 13:
                if (g) freeGraph(g);
                return 0;

            default:
                printf("Invalid choice. Try again.\n");
        }
    }
}


