#include "vertices.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Struct graph provided from PDF
struct Graph {
    uint32_t vertices;
    bool undirected;
    bool visited[VERTICES];
    uint32_t matrix[VERTICES][VERTICES];
};

// graph_create prvided from PDF
Graph *graph_create(uint32_t vertices, bool undirected) {
    Graph *G = (Graph *) calloc(1, sizeof(Graph)); // Allocates memory for graph
    G->vertices = vertices; // Initializes variables with parameters
    G->undirected = undirected;
    return G;
}

// graph_delete provided from PDF
void graph_delete(Graph **G) {
    free(*G); // Frees memory of graph
    *G = NULL;
}

// Returns number of vertices in the graph
uint32_t graph_vertices(Graph *G) {
    return G->vertices;
}

// returns true or false based on if an edge can be added or not
bool graph_add_edge(Graph *G, uint32_t i, uint32_t j, uint32_t k) {
    if (i < G->vertices && j < G->vertices) { // Checks if vertices are within bounds
        if (G->undirected) {
            G->matrix[i][j] = k;
            G->matrix[j][i] = k; // Sets edge weight going both ways between 2 nodes if undirected
        } else {
            G->matrix[i][j] = k; // Sets edge weight going one way
        }
        return true;
    }
    return false;
}

// returns true or false based on edge exists
bool graph_has_edge(Graph *G, uint32_t i, uint32_t j) {
    if ((i < G->vertices && j < G->vertices)
        && G->matrix[i][j] > 0) { // Checks if vertices are within bounds and if an edge exists
        return true;
    }
    return false;
}

// returns weight of edge, or 0 if it doesn't exist
uint32_t graph_edge_weight(Graph *G, uint32_t i, uint32_t j) {
    if ((i < G->vertices && j < G->vertices)
        || G->matrix[i][j] > 0) { // Checks if graph vertices are within bounds and if edge exists
        return G->matrix[i][j]; // Returns edge if it exists
    }
    return 0;
}

// returns wheter vertice has been visited or not
bool graph_visited(Graph *G, uint32_t v) {
    return G->visited[v];
}

// marks vertice as visited
void graph_mark_visited(Graph *G, uint32_t v) {
    if (v < G->vertices) {
        G->visited[v] = true;
    }
}

// marks vertice as unvisited
void graph_mark_unvisited(Graph *G, uint32_t v) {
    if (v < G->vertices) {
        G->visited[v] = false;
    }
}

void graph_print(Graph *G) {
    // Prints vertices and undirected values
    printf("Vertices: %d\n", G->vertices);
    printf("Undirected: %d\n", G->undirected);
    // Prints Matrix
    for (uint32_t i = 0; i < G->vertices; i++) {
        for (uint32_t j = 0; j < G->vertices; j++) {
            printf("%d ", G->matrix[i][j]);
        }
        printf("\n");
    }
}