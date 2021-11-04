#include "path.h"

#include "graph.h"
#include "stack.h"
#include "vertices.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Struct provided in PDF
struct Path {
    Stack *vertices;
    uint32_t length;
};

// Constructor for path
Path *path_create(void) {
    Path *p = (Path *) calloc(1, sizeof(Path)); // Allocates memory for path
    p->vertices = stack_create(VERTICES);
    p->length = 0;
    return p;
}

// Deconsturctor for path
void path_delete(Path **p) {
    stack_delete(&(*p)->vertices); // Deletes stack
    if (*p) {
        free(*p); // Frees memory of path
        *p = NULL;
    }
    return;
}

// Returns true or false based on if vertex is pushed to path and adds respective weight
bool path_push_vertex(Path *p, uint32_t v, Graph *G) {
    uint32_t peek;
    stack_peek(p->vertices, &peek);
    if (stack_push(p->vertices, v)) { // Checks if stack is pushable
        if (stack_size(p->vertices)
            == 1) { // If stack size is 1, add edges of vertex and start vertex
            p->length += graph_edge_weight(G, START_VERTEX, v);
            return true;
        } else {
            p->length += graph_edge_weight(G, peek, v); // Adds edge of vertex and peak
            return true;
        }
    }
    return false;
}

// Returns true or false based on if vertex is popped from path and subtracts respective weight
bool path_pop_vertex(Path *p, uint32_t *v, Graph *G) {
    uint32_t popped;
    if (stack_pop(p->vertices, &popped)) { //
        *v = popped;
        if (stack_size(p->vertices)
            == 0) { // If it's empty, subtract length from start vertex and popped vertex
            p->length -= graph_edge_weight(G, START_VERTEX, popped);
            return true;
        } else {
            uint32_t peek;
            stack_peek(p->vertices, &peek); // Subtracts edge from peak vertice and popped vertice
            p->length -= graph_edge_weight(G, peek, popped);
            return true;
        }
    }
    return false;
}

// Returns number of vertics in path
uint32_t path_vertices(Path *p) {
    return stack_size(p->vertices);
}

// Returns length of the path
uint32_t path_length(Path *p) {
    return p->length;
}

// Copies path from source path to destination path
void path_copy(Path *dst, Path *src) {
    stack_copy(dst->vertices, src->vertices); // Copies stack
    dst->length = src->length; // Copies length
    return;
}