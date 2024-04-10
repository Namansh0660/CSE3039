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




#include <stdio.h>
#include <limits.h>

#define MAX_NODES 10

// Structure to represent a node in the network
struct Node {
    int id;  // Node ID
    int cost[MAX_NODES];  // Cost to other nodes
    int via[MAX_NODES];   // Next hop for each destination
};

// Function to initialize a node
void initNode(struct Node *node, int id, int cost[MAX_NODES], int numNodes) {
    node->id = id;
    for (int i = 0; i < numNodes; i++) {
        node->cost[i] = cost[i];
        node->via[i] = i;  // Initially, via itself
    }
}

// Function to update node's routing table based on received updates
void updateRoutingTable(struct Node *node, struct Node *received, int numNodes) {
    for (int i = 0; i < numNodes; i++) {
        for (int j = 0; j < numNodes; j++) {
            int altCost = node->cost[i] + received->cost[j];
            if (altCost < node->cost[j]) {
                node->cost[j] = altCost;
                node->via[j] = received->id;
            }
        }
    }
}

// Function to print a node's routing table
void printRoutingTable(struct Node *node, int numNodes) {
    printf("Routing table for Node %d:\n", node->id);
    printf("Destination\tNext Hop\tCost\n");
    for (int i = 0; i < numNodes; i++) {
        printf("%d\t\t%d\t\t%d\n", i, node->via[i], node->cost[i]);
    }
    printf("\n");
}

int main() {
    int numNodes;
    printf("Enter the number of nodes: ");
    scanf("%d", &numNodes);

    struct Node nodes[MAX_NODES];
    int cost[MAX_NODES];

    // Input costs for each link
    for (int i = 0; i < numNodes; i++) {
        for (int j = 0; j < numNodes; j++) {
            if (i == j) {
                cost[j] = 0;
                continue;
            }
            printf("Enter cost from Node %d to Node %d: ", i, j);
            scanf("%d", &cost[j]);
        }

        initNode(&nodes[i], i, cost, numNodes);
    }

    // Simulating distance vector routing
    for (int k = 0; k < numNodes; k++) {
        for (int i = 0; i < numNodes; i++) {
            for (int j = 0; j < numNodes; j++) {
                if (i != j) {
                    updateRoutingTable(&nodes[i], &nodes[j], numNodes);
                }
            }
        }
    }

    // Printing the weighted graph
    printf("Weighted Graph:\n");
    for (int i = 0; i < numNodes; i++) {
        printRoutingTable(&nodes[i], numNodes);
    }

    return 0;
}



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
        for (j = 0; j < network->num_nodes; j++) {
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
                    network->routing_table[node][j].next_hop = i;
                }
            }
        }
    }
}

void printRoutingTable(NetworkGraph *network, int node) {
    int i;
    printf("Routing Table for Node %c:\n", 'A' + node);
    printf("Destination\tCost\tNext Hop\n");
    for (i = 0; i < network->num_nodes; i++) {
        printf("%c\t\t%d\t%c\n", 'A' + i, network->routing_table[node][i].cost, 'A' + network->routing_table[node][i].next_hop);
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
