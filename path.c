#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdbool.h>

#include "path.h"
#include "stack.h"
#include "graph.h"
#include "vertices.h"


//STRUCT CODE PROVIDED BY PROF LONG
struct Path{
    Stack *vertices;    // the vertices comprising the path
    uint32_t length;    // the total length of the path
};


//Constructor function for path
Path *path_create(void){
    Path *p = (Path *) calloc(1, sizeof(Path));          // dynamically allocate space for the graph
    p -> vertices = stack_create(VERTICES);
    p -> length = 0; // tracks the length of the path (holds the sum of the edge weights)
    return p;
}

//Destructor function for path
void path_delete(Path **p){
    stack_delete(&(*p)->vertices);                   // deletes the stack and frees the memory
    if(*p){
        free(*p);                                        //free the memory allocated for p
        *p = NULL;
    }
    return;
}

//Pushes vertex v onto path p
bool path_push_vertex(Path *p, uint32_t v, Graph *G){
    uint32_t push;                                      // initialize x variable for memory address of the top element of stack
    stack_peek(p -> vertices, &push);                   // set the variable
    if(stack_push(p -> vertices, v)){                   // if the point was succesfully pushed to path
        if(stack_size(p -> vertices) == 1){
            p -> length += graph_edge_weight(G, START_VERTEX, v);   // if the array is 1 long, then store edge weight of first element to the next one 
            return true;
        }
        else{
            p -> length += graph_edge_weight(G, push, v);           // else add the edge weight of the top element to length
            return true;
        }
    }
    return false;
}

bool path_pop_vertex(Path *p, uint32_t *v, Graph *G){
    uint32_t pop;
    if(stack_pop(p -> vertices, &pop)){                              // pop has the popped value
        *v = pop;                                                   // pointer v points to popped value
        if(stack_size(p -> vertices) == 0){
            p -> length -= graph_edge_weight(G, START_VERTEX, pop); // length subtracted by edge weight of top element of stack
            return true;
        }
        else{
            uint32_t peek;
            stack_peek(p -> vertices, &peek);                       // peek the top element
            p -> length -= graph_edge_weight(G, peek, pop);         // subtract the length by the weight of the edge from the peeked value to the value after it
            return true;
        }
    }
    return false;
}

//returns the number of vertices in the path
uint32_t path_vertices(Path *p){
    return(stack_size(p -> vertices));
}

//returns the length of the path
uint32_t path_length(Path *p){
    return p -> length;
}

//makes dst a copy of the source path (src)
void path_copy(Path *dst, Path *src){
    stack_copy(dst -> vertices, src -> vertices);             // copy the path to dst from src
    dst -> length = src -> length;                            // copy the src length to dst length
    return;
}

//print the vertices
void path_print(Path *p, FILE *outfile, char *cities[]){
    stack_print(p -> vertices, outfile, cities);
}