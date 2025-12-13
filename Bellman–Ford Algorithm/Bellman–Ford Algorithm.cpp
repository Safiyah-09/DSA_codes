#include <iostream>
#include <climits>
using namespace std;

// Structure to represent a delivery route (edge)
struct Edge {
    int src, dest, weight; // weight = distance or traffic delay
};

// Bellman-Ford Algorithm
void bellmanFord(Edge edges[], int V, int E, int source) {
    int distance[V];

    // Step 1: Initialize distances
    for (int i = 0; i < V; i++)
        distance[i] = INT_MAX;

    distance[source] = 0;

    // Step 2: Relax all edges V-1 times
    for (int i = 1; i <= V - 1; i++) {
        for (int j = 0; j < E; j++) {
            int u = edges[j].src;
            int v = edges[j].dest;
            int w = edges[j].weight;

            if (distance[u] != INT_MAX && distance[u] + w < distance[v]) {
                distance[v] = distance[u] + w;
            }
        }
    }

    // Step 3: Check for negative weight cycles
    for (int j = 0; j < E; j++) {
        int u = edges[j].src;
        int v = edges[j].dest;
        int w = edges[j].weight;

        if (distance[u] != INT_MAX && distance[u] + w < distance[v]) {
            cout << "Traffic cycle detected (negative cycle exists).\n";
            return;
        }
    }

    // Output shortest delivery times
    cout << "\nFastest delivery time from Restaurant:\n";
    for (int i = 0; i < V; i++) {
        cout << "To Location " << i << " : ";
        if (distance[i] == INT_MAX)
            cout << "Unreachable\n";
        else
            cout << distance[i] << " minutes\n";
    }
}

int main() {
    int V = 5;  // Delivery locations (including restaurant)
    int E = 8;  // Number of routes

    // Graph edges (src, dest, time/traffic delay)
    Edge edges[] = {
        {0, 1, 6},   // Restaurant to Area 1
        {0, 2, 7},   // Restaurant to Area 2
        {1, 2, 8},
        {1, 3, 5},
        {1, 4, -4},  // Traffic shortcut
        {2, 3, -3},
        {2, 4, 9},
        {3, 1, -2}
    };

    int source = 0; // Restaurant location

    bellmanFord(edges, V, E, source);

    return 0;
}
