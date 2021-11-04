#include <stdio.h>
#include <stdlib.h>4
#include <inttypes.h>
#include <stdbool.h>

#include "graph.h"
#include "vertices.h"

// GRAPH STRUCT CODE PROVIDED BY PROF LONG
struct Graph {
    uint32_t vertices;
    bool undirected;
    bool visited[VERTICES];
    uint32_t matrix[VERTICES][VERTICES];    
};

// GRAPH CONSTRUCTOR CODE PROVIDED BY PROF LONG
//constructor for a graph
Graph *graph_create(uint32_t vertices, bool undirected){
    Graph *G = (Graph *) calloc(1, sizeof(Graph));          // dynamically allocate space for the graph
    G -> vertices = vertices;                               // initialize vertices to graph vertices
    G -> undirected = undirected;                           // initialize undirected to graph undirected
    return G;                                               // return the pointer to the start of memory that's been allocated
}

// GRAPH DESTRUCTOR CODE PROVIDED BY PROF LONG
//destructor for a graph (frees all of the memory allocated by the computer)
void graph_delete(Graph **G){
    free(*G);                                               // free the memory allocated space since it uses calloc()
    *G = NULL;                                              
}

//Accesor Function that returns the number of vertices in a graph
uint32_t graph_vertices(Graph *G){
    return G->vertices;
}

//Manipulator Function that adds an edge to the graph
bool graph_add_edge(Graph *G, uint32_t i, uint32_t j, uint32_t k){
    //check if vertices are within bounds
    if(i < G -> vertices && j < G -> vertices){
        if(G -> undirected){                        // if undirected, add undirected edge
            G -> matrix[i][j] = k; 
            G -> matrix[j][i] = k;
            //return true;                                    // return true when both vertices are within bounds an d edges are added  
        }
        else{                                               // if directed, add a directed edge
            G -> matrix[i][j] = k;
            //return true;                                    // return true when both vertices are within bounds an d edges are added 
        }
        return true;                                    // return true when both vertices are within bounds an d edges are added  
    }
    return false;                                           // return false when edges are NOT in bounds and are not added
}

//return true if vertices i and j are within bounds and there exists an edge from i to j 
bool graph_has_edge(Graph *G, uint32_t i, uint32_t j){
    if((i < G -> vertices && j < G -> vertices) && G->matrix[i][j] > 0){                     // if both vertices are in bounds 
        return true;
    }
    return false; // return false if any one of the vertices are out of bounds
}

//returns the weight of the edge from vertex i to vertex j
uint32_t graph_edge_weight(Graph *G, uint32_t i, uint32_t j){
    if(((i < G -> vertices && j < G -> vertices) || G -> matrix[i][j]) > 0){           // if vertices are in bounds
        return G -> matrix[i][j]; 
    }
        return 0;
}

//return true if vertex v has been visited
bool graph_visited(Graph *G, uint32_t v){
    return G -> visited[v];
}

//if the vertex v is within bounds, then mark it as visited
void graph_mark_visited(Graph *G, uint32_t v){
    if(v < G -> vertices){                                 // if given vertex is within the bounds of the max number of vertices
        G -> visited[v] = true;
    }
}

//if the vertex v is within bounds, mark v as unvisited
void graph_mark_unvisited(Graph *G, uint32_t v){
    if(v < G -> vertices){                                // if given vertex is within the bounds of the max number of vertices
        G -> visited[v] = false;
    }
}

//Print Graph function for testing
void graph_print(Graph *G) {
    // print the vertices and undirected values
    printf("Vertices: %d\n", G->vertices);
    printf("Undirected: %d\n", G->undirected);
    // Print the matrix
    for (uint32_t i = 0; i < G->vertices; i++) {
        for (uint32_t j = 0; j < G->vertices; j++) {
            printf("%d ", G->matrix[i][j]);
        }
        printf("\n");
    }
}