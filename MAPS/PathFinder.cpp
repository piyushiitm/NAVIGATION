#include <iostream>                 // For input/output
#include <vector>                   // To use vectors
#include <queue>                    // For priority queue in Dijkstra
#include <climits>                  // For INT_MAX
#include "Map.h"                  // Include our graph module
using namespace std;

// Dijkstra algorithm to find shortest path from start to end
vector<int> dijkstra(Graph &g, int start, int end) {
    int n = g.maxNode;                       // Total number of nodes
    vector<int> dist(n + 1, INT_MAX);        // Distance from start to each node, initialize to infinity
    vector<int> parent(n + 1, -1);           // To store parent of each node for path reconstruction

    dist[start] = 0;                          // Distance from start to itself is 0

    // Priority queue (min-heap) to always pick node with smallest distance
    // Stores pair: (distance, node)
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    pq.push({0, start});                      // Start with the start node

    while (!pq.empty()) {                     // While there are nodes to process
        int uDist = pq.top().first;           // Distance of current node from start
        int u = pq.top().second;             // Node number
        pq.pop();                             // Remove it from queue

        if (uDist > dist[u]) continue;        // Skip if we already found a shorter path to this node

        for (auto edge : g.adjacencyList[u]) {   // Check all neighbors of u
            int v = edge.neighbor;               // Neighbor node
            int w = edge.weight;                 // Weight of edge u -> v

            if (dist[u] + w < dist[v]) {         // If new path is shorter
                dist[v] = dist[u] + w;           // Update distance
                parent[v] = u;                   // Update parent to reconstruct path later
                pq.push({dist[v], v});           // Add neighbor to queue
            }
        }
    }

    // Reconstruct the shortest path from start to end
    vector<int> path;
    if (dist[end] == INT_MAX) return path;     // If distance is infinity, no path exists

    int node = end;                             // Start from end node
    while (node != -1) {                        // Trace back using parent array
        path.push_back(node);                   // Add node to path
        node = parent[node];                    // Move to parent
    }
    reverse(path.begin(), path.end());           // Reverse path to start -> end
    return path;                                 // Return the path
}

int main() {
    Graph g("MainBlock.csv");                   // Load graph from CSV file
    g.display_map();                             // Optional: print adjacency list for verification
    g.displayNodes();
    int start;                              // Starting node ID (Entrance)
    int end;                               // Ending node ID (Reception)
    cout<<"Enter Starting node:";
    cin>>start;
    cout<<"Enter Ending Node";
    cin>>end;
    // Call Dijkstra algorithm to get shortest path
    vector<int> path = dijkstra(g, start, end);

    // Print the shortest path using labels
    cout << "\nShortest path from " << g.idToLabel[start] << " to " << g.idToLabel[end] << ":\n";
    for (int i = 0; i < path.size(); i++) {
        cout << g.idToLabel[path[i]];           // Print label of each node in path
        if (i != path.size() - 1) cout << " -> "; // Add arrow between nodes
    }
    cout << endl;                               // End the line

    return 0;                                   // Program finished
}
