#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#include "stack.h"
#include "vertices.h"

// STACK STRUCT CODE PROVIDED BY PROF LONG
struct Stack {
    uint32_t top;                                                           // index of the next empty slot
    uint32_t capacity;                                                      // the max number of items that can be pushed
    uint32_t *items;                                                        // an array of items, each of type uint32_t integers (32 bit integers)
};

// Constructor function for stack
Stack *stack_create(uint32_t capacity){
    Stack *s = (Stack *) malloc(sizeof(Stack));                             // dynamically allocate memory for the stack 
    if(s){
        s -> top = 0;                                                       // index of next empty slot of the stack is 0
        s -> capacity = capacity;                                           // the max number of items that can be pushed is passed in as a paramater
        s -> items = (uint32_t *) calloc(capacity, sizeof(uint32_t));       // dynamically allocate memory for array of items
        if(!s -> items){
            free(s);                                                        // free the memory
            s = NULL;
        }
    }
    return s;
}

// Destructor function for stack
void stack_delete(Stack **s){
    if(*s && (*s) -> items){
        free((*s) -> items);                                                // free the items array memory
        free(*s);                                                           // free the stack memory
        *s = NULL;
    }
    return;
}

//returns true if the stack is empty and false otherwise
bool stack_empty(Stack *s){
    if(s -> top == 0){ 
        return true;
    }
        return false;
}

//returns true if the stack is full and false otherwise
bool stack_full(Stack *s){
    if(s -> top == s-> capacity){ // if the next index is the capacity -1 (meaning the stack is full)
        return true;
    }
        return false;
}

//returns the number of items in the stack
uint32_t stack_size(Stack *s){
    return s -> top;
}

//pushes an item x to the top of the stack
bool stack_push(Stack *s, uint32_t x){
    if(stack_full(s)){                                              // if stack is full, return false
        return false;
    }
    else{                                                           // if stack is not full, then push and return true
        s -> items[s -> top] = x;
        s -> top++;                                                 // increment top to point at next spot in stack
        return true;
    }
}

//pops an item off of the specified stack
bool stack_pop(Stack *s, uint32_t *x){
    if(stack_empty(s)){                                             // if the stack is empty, return false
        return false;
    }
    else{
        *x = s -> items[s -> top];                               // set *x equal to the value at the top of the stack
        s -> items[s -> top] = 0;                                 // set popped value to 0
        s -> top--;                                                 //decrement top to point in previous spot in stack
        return true;
    }
}

//query about the element at the top of a stack
bool stack_peek(Stack *s, uint32_t *x){
    if(stack_empty(s)){                                             // return false if the stack is empty
        return false;
    }
    else{
        *x = s -> items[s -> top -1];                               // set *x equal to the value at the top of the stack
        return true;
    }
}

//makes dst a copy of src
void stack_copy(Stack *dst, Stack *src){
    //copy the contents of src -> items[]into dst -> items[]
    for(uint32_t i = 0; i < src -> capacity; i++){
        dst -> items[i] = src -> items[i];
    }
    dst -> top = src -> top;
    return;
}

// CODE PROVIDED BY PROF LONG
// Prints out contents of stack to outfile
void stack_print ( Stack *s, FILE * outfile , char * cities []) {
    for ( uint32_t i = 0; i < s->top; i += 1) {
        fprintf ( outfile , "%s", cities [s-> items [i]]) ;
        if (i + 1 != s->top ) {
            fprintf ( outfile , " -> ") ;
        }
    }
    fprintf ( outfile , "\n");
}