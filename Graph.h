#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;
const int MAX_NODES = 100; // Adjust based on the maximum number of unique nodes in the graph

struct Edge {
    int vertexIndex; // Index of the adjacent vertex
    int weight;      // Weight of the edge
    Edge* next;     // Pointer to the next edge (for the linked list)
};


struct Graph {
    string vertices[MAX_NODES]; // Stores the names of the vertices
    Edge* adjacencyList[MAX_NODES];  // Array of pointers to adjacency lists
    int vertexCount; // Keeps track of the number of unique vertices

    // Constructor
    Graph() : vertexCount(0) {
        for (int i = 0; i < MAX_NODES; i++) {
            adjacencyList[i] = nullptr; // Initialize all adjacency lists as empty
        }
    }

    // Get the index of a vertex, or add it if it doesn't exist
    int getVertexIndex(const string& vertex) {
        for (int i = 0; i < vertexCount; i++) {
            if (vertices[i] == vertex) {
                return i;
            }
        }
        // If vertex is not found, add it
        if (vertexCount < MAX_NODES) {
            vertices[vertexCount] = vertex;
            return vertexCount++;
        }
        else {
            cout << "Error: Exceeded maximum number of vertices.\n";
            return -1;
        }
    }

    // Add an edge to the adjacency list
    void addEdge(int vertex1, int vertex2, int weight) {
        // Add edge from vertex1 to vertex2
        Edge* newEdge1 = new Edge{ vertex2, weight, adjacencyList[vertex1] };
        adjacencyList[vertex1] = newEdge1;

        // Add edge from vertex2 to vertex1 (undirected graph)
        Edge* newEdge2 = new Edge{ vertex1, weight, adjacencyList[vertex2] };
        adjacencyList[vertex2] = newEdge2;
    }

    // Print the adjacency list
    void printAdjacencyList() {
        for (int i = 0; i < vertexCount; i++) {
            cout << vertices[i] << ": ";
            Edge* current = adjacencyList[i];
            while (current) {
                cout << "(" << vertices[current->vertexIndex] << ", " << current->weight << ") ";
                current = current->next;
            }
            cout << "\n";
        }
    }

    // Print vertices
    void printVertices() {
        for (int i = 0; i < vertexCount; i++) {
            cout << i + 1 << "." << " " << vertices[i] << endl;
        }
        
    }

    // Dijkstra algorithm for shortest path
    int dijkstra(int start, int end) {
        int dist[MAX_NODES]; // Distance from start to each vertex
        bool visited[MAX_NODES] = { false }; // Visited vertices
        int parent[MAX_NODES]; // For path tracking

        // Initialize distances
        for (int i = 0; i < vertexCount; i++) {
            dist[i] = INT_MAX;
            parent[i] = -1;
        }

        dist[start] = 0; // Distance to start is 0

        // Custom priority queue implementation
        struct PriorityQueue {
            int nodes[MAX_NODES];
            int weights[MAX_NODES];
            int size;

            PriorityQueue() : size(0) {}

            void push(int node, int weight) {
                nodes[size] = node;
                weights[size] = weight;
                size++;
            }

            int pop() {
                int minIndex = 0;
                for (int i = 1; i < size; i++) {
                    if (weights[i] < weights[minIndex]) {
                        minIndex = i;
                    }
                }
                int minNode = nodes[minIndex];
                // Remove the min node by shifting
                for (int i = minIndex; i < size - 1; i++) {
                    nodes[i] = nodes[i + 1];
                    weights[i] = weights[i + 1];
                }
                size--;
                return minNode;
            }

            bool isEmpty() {
                return size == 0;
            }
        };

        PriorityQueue pq;
        pq.push(start, 0);

        while (!pq.isEmpty()) {
            int currentVertex = pq.pop();

            if (visited[currentVertex]) continue;
            visited[currentVertex] = true;

            Edge* currentEdge = adjacencyList[currentVertex];
            while (currentEdge) {
                int neighbor = currentEdge->vertexIndex;
                int weight = currentEdge->weight;

                // Relaxation step
                if (!visited[neighbor] && dist[currentVertex] + weight < dist[neighbor]) {
                    dist[neighbor] = dist[currentVertex] + weight;
                    parent[neighbor] = currentVertex;
                    pq.push(neighbor, dist[neighbor]);
                }

                currentEdge = currentEdge->next;
            }
        }

        // Return the shortest distance to the end vertex
        if (dist[end] == INT_MAX) {
            cout << "No path found between vertices.\n";
            return -1;
        }
        return dist[end];
    }



    string dijkstraPath(int start, int end) {
        int dist[MAX_NODES]; // Distance from start to each vertex
        bool visited[MAX_NODES] = { false }; // Visited vertices
        int parent[MAX_NODES]; // For path tracking

        // Initialize distances
        for (int i = 0; i < vertexCount; i++) {
            dist[i] = INT_MAX;
            parent[i] = -1;
        }

        dist[start] = 0; // Distance to start is 0

        // Custom priority queue implementation
        struct PriorityQueue {
            int nodes[MAX_NODES];
            int weights[MAX_NODES];
            int size;

            PriorityQueue() : size(0) {}

            void push(int node, int weight) {
                nodes[size] = node;
                weights[size] = weight;
                size++;
            }

            int pop() {
                int minIndex = 0;
                for (int i = 1; i < size; i++) {
                    if (weights[i] < weights[minIndex]) {
                        minIndex = i;
                    }
                }
                int minNode = nodes[minIndex];
                // Remove the min node by shifting
                for (int i = minIndex; i < size - 1; i++) {
                    nodes[i] = nodes[i + 1];
                    weights[i] = weights[i + 1];
                }
                size--;
                return minNode;
            }

            bool isEmpty() {
                return size == 0;
            }
        };

        PriorityQueue pq;
        pq.push(start, 0);

        while (!pq.isEmpty()) {
            int currentVertex = pq.pop();

            if (visited[currentVertex]) continue;
            visited[currentVertex] = true;

            Edge* currentEdge = adjacencyList[currentVertex];
            while (currentEdge) {
                int neighbor = currentEdge->vertexIndex;
                int weight = currentEdge->weight;

                // Relaxation step
                if (!visited[neighbor] && dist[currentVertex] + weight < dist[neighbor]) {
                    dist[neighbor] = dist[currentVertex] + weight;
                    parent[neighbor] = currentVertex;
                    pq.push(neighbor, dist[neighbor]);
                }

                currentEdge = currentEdge->next;
            }
        }

        // If no path is found, return an error message
        if (dist[end] == INT_MAX) {
            return "No path found between vertices.";
        }

        // Reconstruct the shortest path using the parent array
        string path = "";
        int current = end;
        while (current != -1) {
            if (!path.empty()) {
                path = " -> " + path; // Add separator before each node (except the first one)
            }
            path = vertices[current] + path;
            current = parent[current];
        }

        // Return the path with total weight
        stringstream result;
        result << "Shortest path: " << path << " (Weight: " << dist[end] << ")";
        return result.str();
    }



    // 
    int getLocationIndex(string location) {
        for (int i = 0; i < vertexCount; i++) {
            if (vertices[i] == location) return i;
        }

    }

};

