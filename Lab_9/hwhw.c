#include <stdio.h>

#define MAX_NODES 10
#define INFINITY 9999

int cost[MAX_NODES][MAX_NODES];
int distance[MAX_NODES];
int nextHop[MAX_NODES];

void init(int n) {
    for (int i = 0; i < n; i++) {
        distance[i] = INFINITY;
        nextHop[i] = -1;
    }
}

void distanceVector(int n) {
    int updated;

    do {
        updated = 0;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (distance[i] > distance[j] + cost[j][i]) {
                    distance[i] = distance[j] + cost[j][i];
                    nextHop[i] = j;
                    updated = 1;
                }
            }
        }
    } while (updated);
}

void printGraph(int n) {
    printf("Weighted Graph:\n");
    printf("Node  Cost  Next Hop\n");
    for (int i = 0; i < n; i++) {
        printf("%c     %d     %c\n", 'A' + i, distance[i], 'A' + nextHop[i]);
    }
    printf("\n");
}

void printRoutingTable(int node, int n) {
    printf("Routing Table for Node %c:\n", 'A' + node);
    printf("Destination  Cost  Next Hop\n");
    for (int i = 0; i < n; i++) {
        printf("%c            %d     %c\n", 'A' + i, distance[i], 'A' + nextHop[i]);
    }
    printf("\n");
}

int main() {
    int n;

    printf("Enter the number of nodes: ");
    scanf("%d", &n);

    printf("Enter the cost of links:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &cost[i][j]);
        }
    }

    init(n);
    distanceVector(n);
    printGraph(n);

    for (int i = 0; i < n; i++) {
        init(n);
        distance[i] = 0;  // Initialize distance for current node to 0
        distanceVector(n);
        printRoutingTable(i, n);
    }

    return 0;
}
