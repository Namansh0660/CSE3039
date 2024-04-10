#include <stdio.h>
#include <limits.h>

#define MAX_NODES 10

typedef struct {
    int cost;
    int next_hop;
} RoutingEntry;

typedef struct {
    int graph[MAX_NODES][MAX_NODES];
    RoutingEntry routing_table[MAX_NODES][MAX_NODES];
    int num_nodes;
} NetworkGraph;

void initializeGraph(NetworkGraph *network) {
    int i, j;
    for (i = 0; i < network->num_nodes; i++) {
        for (j = 0; j < network->num_nodes; j++) {
            if (i == j) {
                network->graph[i][j] = 0;
            } else {
                network->graph[i][j] = INT_MAX;
            }
        }
    }
}

void addLink(NetworkGraph *network, int node1, int node2, int cost) {
    network->graph[node1][node2] = cost;
    network->graph[node2][node1] = cost;
}

void printGraph(NetworkGraph *network) {
    int i, j;
    printf("Weighted Graph:\n");
    for (i = 0; i < network->num_nodes; i++) {
        for (j = i+1; j < network->num_nodes; j++) {
            if (network->graph[i][j] != INT_MAX) {
                printf("%c - %c : %d\n", 'A' + i, 'A' + j, network->graph[i][j]);
            }
        }
    }
}

void calculateRoutingTable(NetworkGraph *network, int node) {
    int i, j, k;
    for (i = 0; i < network->num_nodes; i++) {
        network->routing_table[node][i].cost = network->graph[node][i];
        network->routing_table[node][i].next_hop = i;
    }

    for (k = 0; k < network->num_nodes; k++) {
        for (i = 0; i < network->num_nodes; i++) {
            for (j = 0; j < network->num_nodes; j++) {
                int new_cost = network->routing_table[node][i].cost + network->graph[i][j];
                if (new_cost < network->routing_table[node][j].cost) {
                    network->routing_table[node][j].cost = new_cost;
                    //network->routing_table[node][j].next_hop = i;
                    network->routing_table[node][j].next_hop = network->routing_table[node][i].next_hop;
                }
            }
        }
    }
}

void printRoutingTable(NetworkGraph *network, int node) {
    int i;
    printf("Routing Table for Node %c:\n", 'A' + node);
    printf("Destination\tCost\n");
    for (i = 0; i < network->num_nodes; i++) {
        //printf("%c\t\t%d\t%c\n", 'A' + i, network->routing_table[node][i].cost, 'A' + network->routing_table[node][i].next_hop);
          printf("%c\t\t%d\n", 'A' + i, network->routing_table[node][i].cost);
    }
}

int main() {
    NetworkGraph network;
    int num_nodes, i, j, cost;

    printf("Enter the number of nodes: ");
    scanf("%d", &num_nodes);

    network.num_nodes = num_nodes;
    initializeGraph(&network);

    for (i = 0; i < num_nodes; i++) {
        for (j = i + 1; j < num_nodes; j++) {
            printf("Enter the cost of link %c to %c: ", 'A' + i, 'A' + j);
            scanf("%d", &cost);
            addLink(&network, i, j, cost);
        }
    }

    printGraph(&network);

    for (i = 0; i < num_nodes; i++) {
        calculateRoutingTable(&network, i);
        printRoutingTable(&network, i);
    }

    return 0;
}
