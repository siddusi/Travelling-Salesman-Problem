#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdbool.h>
#include <unistd.h> // needed for getopt()
#include <string.h> // needed for strcpy()

#include "path.h"
#include "stack.h"
#include "graph.h"
#include "vertices.h"

#define OPTIONS "hvui:o:" // -r and -n will both have arguments

//Variables
static uint32_t iteration = 0;             //keeps track of the number of iterations in DFS
static uint32_t recursion = 1;          // initialize recursion to keep track of number calls to DFS

//HELPER FUCNTIONS
//print function
void print_info(Path *p, FILE *outfile, char **cities){
    fprintf(outfile, "Path length: %"PRIu32 "\n", path_length(p));
    fprintf(outfile, "Path: ");
    path_print(p, outfile, cities);
}

// PSEUDOCODE PROVIDED BY PROF LONG 
// DFS function

void DFS(Graph *G, Path *current, Path *shortest, uint32_t v, FILE *outfile, char*cities[], bool verbose){
    uint32_t temp;                                                                                  // initialize temporary value to hold the popped value
    //BASE CASE
    if(graph_has_edge(G, v, START_VERTEX) && path_vertices(current) == graph_vertices(G)){
        path_push_vertex(current, START_VERTEX, G);                                                 // push origin back to the stack so you end up back at the origin
        iteration++;                                                                               // increment iteration
        if(iteration == 1){
            path_copy(shortest, current);                                                           // shortest path = the current path
        }
        else if(path_length(current) < path_length(shortest)){
            path_copy(shortest, current);                                                           // shortest path = the current path
        }
        if(verbose){ // if the verbose function was requested
            print_info(current,outfile,cities);  // print every single path
        }
        path_pop_vertex(current, &temp, G);                                                         // pop the origin to find a new path
        return;                                                                                     // end the recursion
    }

    //MAIN RECURSION
    graph_mark_visited(G, v);                                                                       // label v as visited
    for(uint32_t w = START_VERTEX; w < graph_vertices(G); w++){                                    // go through all vertices in the graph
        if(graph_has_edge(G, v, w)){                                                                // check if the loop vertex is an edge of the vertex (v)
            if(graph_visited(G,w) == false){                                                                 // make sure that the loop vertex has not been visited
                path_push_vertex(current, w, G);                                                    // push current loop vertex onto the current working path
                recursion += 1;                                                                     // increment recursion to keep track of number of calls to DFS
                DFS(G, current, shortest, w, outfile, cities, verbose);                                                       // recursive call to DFS on the current loop vertex
                path_pop_vertex(current, &temp, G);                                                 // make sure to pop DFS call out of stack memory
            }
        }
    }
    graph_mark_unvisited(G, v);                                                                     // label v as unvisited
}

//MAIN FUNCTION
int main(int argc, char **argv){
    //Variables
    int opt = 0;
    Graph *g = graph_create(26,false); // temporary graph made to run program
    FILE *in_file = stdin;          // initialize to default value of stdin
    FILE *out_file = stdout;        // initialize to default value of stdin
    Path *current = path_create();  // initialize current path
    Path *shortest = path_create(); // initialize shortest path
    path_push_vertex(current,START_VERTEX,g);
    char line[50];                  // initialize char array (line) to read file lines into
    uint32_t vertices;              // vertices variable to hold the num of vertices specified in files
    bool undirected = false;            // initialize boolean undirected to be false
    bool verbose = false;               // initialize boolean verbose to be false
    bool no_input = false;

    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        no_input = true;
        switch (opt) {
        case 'h': // Help message
            printf("SYNOPSIS\n");
            printf("  Traveling Salesman Problem using DFS.\n");
            printf("\n");
            printf("USAGE\n");
            printf("  ./tsp [-u] [-v] [-h] [-i infile] [-o outfile]\n");
            printf("\n");
            printf("OPTIONS\n");
            printf("  -u             Use undirected graph.\n");
            printf("  -v             Enable verbose printing.\n");
            printf("  -h             Program usage and help.\n");
            printf("  -i infile      Input containing graph (default: stdin)\n");
            printf("  -o outfile     Output of computed path (default: stdout)\n");
        case 'v': // enables verbose printing
            verbose = true;
            break;
        case 'u': // specifies the graph to be undirected
            undirected = true;
            break;
        case 'i': // specify the input file
            in_file = fopen(optarg,"r");
            break;
        case 'o': // specify the output file
            out_file = fopen(optarg,"w");
            break;
    }

    //Check in_file validity
    if(in_file == NULL){ // Checks if file is a valid file, if not return error
        printf("Invalid file: failed to open infile.\n");
           return 0;
    }

    // RUN THE PROGRAM!!!

    //Start reading the file
    fgets(line,100,in_file);                            // get the first line from assigned file
    vertices = atoi(line);                              // vertices is assigned the first line of the file
    if(vertices > VERTICES || vertices < 1){            // if it's an invalid vertex, end the program
        printf("Invalid number of vertices.\n");
        return 0;
    }
    char **cities = (char**) calloc(vertices,sizeof(char*));            // dynamically allocate memory for cities
    for(uint32_t i = 0; i < vertices; i++){
        cities[i] = (char*) calloc(100,sizeof(char));                   // dynamically allocate memory for each city in array
    }
    graph_delete(&g);                                                   // delete the temporary graph to free the memory
    g = graph_create(vertices, undirected);                             // Initialize the graph
    for(uint32_t j = 0; j < vertices; j++){                 
        fgets(line,100,in_file);                                        // get the next line
        strcpy(cities[j],strtok(line,"\n"));                            // cities are stored into array
    }
    while(fgets(line,100,in_file) != NULL){                             // loop through all the edges in the file
        uint32_t v1 = atoi(strtok(line," "));              
        uint32_t v2 = atoi(strtok(NULL," "));                           // split each integer into a varaible (v1, v2, or v3)
        uint32_t v3 = atoi(strtok(NULL,"\n"));
        
        graph_add_edge(g,v1,v2,v3);                                     // add the edge to the graph
    }
    fclose(in_file);                                                    // close the file
    DFS(g,current,shortest, START_VERTEX, out_file,cities,verbose);     // run the DFS algo
    print_info(shortest, out_file, cities);                             // print the shortest path
    fprintf(out_file,"Total recursive calls: %"PRIu32"\n", recursion);
    fclose(out_file);
    graph_delete(&g);                                                   // free memory by deleting graph
    for(uint32_t k = 0; k < vertices; k++){                             // free mmeory by deleting all of the cities
        free(cities[k]);
    }
    free(cities);
    path_delete(&current);                                              // delete the current path
    path_delete(&shortest);                                             // delete the shortest path
    return 0;
    }
}