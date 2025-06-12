#include "utils/graph.h"
#include "MST/prim.h"
#include "MST/kruskal.h"
#include "Path/bellmanford.h"
#include "Path/dijkstra.h"
#include <stdio.h>

void showMSTMenu(Graph* g);
void showPathMenu(Graph* g);

int main() {
    Graph* g = NULL;
    int mainChoice;
    char filename[256];
    int vertices, startVertex;
    float density;

    while (1) {
        printf("\n== Main Menu ==\n");
        printf("1. MST algorithms\n");
        printf("2. Shortest Path algorithms\n");
        printf("3. Exit\n");
        printf("Choice: ");
        scanf("%d", &mainChoice);

        switch (mainChoice) {
            case 1:
                showMSTMenu(g);
                break;
            case 2:
                showPathMenu(g);
                break;
            case 3:
                if (g) freeGraph(g);
                return 0;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
}

void showMSTMenu(Graph* g) {
    int choice;
    char filename[256];
    int vertices;
    float density;

    while (1) {
        printf("\n== MST Menu ==\n");
        printf("1. Load graph from file (undirected)\n");
        printf("2. Generate random graph (undirected)\n");
        printf("3. Display matrix\n");
        printf("4. Display adjacency list\n");
        printf("5. Prim's algorithm (Matrix)\n");
        printf("6. Prim's algorithm (List)\n");
        printf("7. Kruskal's algorithm (Matrix)\n");
        printf("8. Kruskal's algorithm (List)\n");
        printf("9. Back to main menu\n");
        printf("Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Filename: ");
                scanf("%s", filename);
                if (g) freeGraph(g);
                g = loadGraphFromFile(filename, false); // Undirected for MST
                if (g) {
                    printf("Graph loaded.\n");
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
                printf("Random undirected graph generated.\n");
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
                return;

            default:
                printf("Invalid choice. Try again.\n");
        }
    }
}

void showPathMenu(Graph* g) {
    int choice;
    char filename[256];
    int vertices, startVertex;
    float density;

    while (1) {
        printf("\n== Shortest Path Menu ==\n");
        printf("1. Load graph from file (directed)\n");
        printf("2. Generate random graph (directed)\n");
        printf("3. Display matrix\n");
        printf("4. Display adjacency list\n");
        printf("5. Dijkstra's algorithm (Matrix)\n");
        printf("6. Dijkstra's algorithm (List)\n");
        printf("7. Bellman-Ford algorithm (Matrix)\n");
        printf("8. Bellman-Ford algorithm (List)\n");
        printf("9. Back to main menu\n");
        printf("Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Filename: ");
                scanf("%s", filename);
                if (g) freeGraph(g);
                g = loadGraphFromFile(filename, true); // Directed for shortest path
                if (g) {
                    printf("Graph loaded.\n");
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
                g = generateRandomDirectedGraph(vertices, density); // Need to implement this
                printf("Random directed graph generated.\n");
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
                if (g) {
                    printf("Start vertex: ");
                    scanf("%d", &startVertex);
                    dijkstraMatrix(g, startVertex);
                } else {
                    printf("Load or generate a graph first.\n");
                }
                break;

            case 6:
                if (g) {
                    printf("Start vertex: ");
                    scanf("%d", &startVertex);
                    dijkstraList(g, startVertex);
                } else {
                    printf("Load or generate a graph first.\n");
                }
                break;

            case 7:
                if (g) {
                    printf("Start vertex: ");
                    scanf("%d", &startVertex);
                    bellmanFordMatrix(g, startVertex);
                } else {
                    printf("Load or generate a graph first.\n");
                }
                break;

            case 8:
                if (g) {
                    printf("Start vertex: ");
                    scanf("%d", &startVertex);
                    bellmanFordList(g, startVertex);
                } else {
                    printf("Load or generate a graph first.\n");
                }
                break;

            case 9:
                return;

            default:
                printf("Invalid choice. Try again.\n");
        }
    }
}