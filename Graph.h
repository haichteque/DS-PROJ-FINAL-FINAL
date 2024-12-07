#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

const int MAX_NODES = 100; // Adjust based on the maximum number of unique nodes in the graph

struct Edge {
    int vertexIndex; // Index of the adjacent vertex
    int weight;      // Weight of the edge
    Edge* next;     // Pointer to the next edge (for the linked list)
};

struct Graph {
    std::string vertices[MAX_NODES]; // Stores the names of the vertices
    Edge* adjacencyList[MAX_NODES];  // Array of pointers to adjacency lists
    int vertexCount; // Keeps track of the number of unique vertices

    // Constructor
    Graph() : vertexCount(0) {
        for (int i = 0; i < MAX_NODES; i++) {
            adjacencyList[i] = nullptr; // Initialize all adjacency lists as empty
        }
    }

    // Get the index of a vertex, or add it if it doesn't exist
    int getVertexIndex(const std::string& vertex) {
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
            std::cerr << "Error: Exceeded maximum number of vertices.\n";
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
            std::cout << vertices[i] << ": ";
            Edge* current = adjacencyList[i];
            while (current) {
                std::cout << "(" << vertices[current->vertexIndex] << ", " << current->weight << ") ";
                current = current->next;
            }
            std::cout << "\n";
        }
    }

    // Print vertices
    void printVertices() {
        for (int i = 0; i < vertexCount; i++) {
            cout << i + 1 << "." << " " << vertices[i] << endl;
        }
        
    }
};

