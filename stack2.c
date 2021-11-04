#include "stack.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Struct definition provided in PDF
struct Stack {
    uint32_t top;
    uint32_t capacity;
    uint32_t *items;
};

// Struct_create function provided in PDF
Stack *stack_create(uint32_t capacity) {
    Stack *s = (Stack *) malloc(sizeof(Stack)); // Allocates memory for stack
    if (s) {
        s->top = 0; // Initializes variables
        s->capacity = capacity;
        s->items = (uint32_t *) calloc(capacity, sizeof(uint32_t)); // Allocates memory for items
        if (!s->items) {
            free(s); // Frees stack
            s = NULL;
        }
    }
    return s;
}

// stack_delete function provided in pdf
void stack_delete(Stack **s) {
    if (*s && (*s)->items) { // Frees both the stack and items array
        free((*s)->items);
        free(*s);
        *s = NULL;
    }
    return;
}

// Retusn true or false based on if stack is empty
bool stack_empty(Stack *s) {
    if (s->top == 0) {
        return true;
    }
    return false;
}

// Returns true of false based on if stack is full
bool stack_full(Stack *s) {
    if (s->top == s->capacity) { // Checks if top indice equals the capacity
        return true;
    }
    return false;
}

// Returns number of items in the stack
uint32_t stack_size(Stack *s) {
    return s->top; // Returns the top indice
}

// Returns true or false based on if element is pushed to stack
bool stack_push(Stack *s, uint32_t x) {
    if (!stack_full(s)) { // Checks if stack is full
        s->items[s->top] = x; // Sets top of stack to the value of x
        s->top++; // Increments top value
        return true;
    }
    return false;
}

// Returns true or false based on if element is popped out of stack, stores popped value in x
bool stack_pop(Stack *s, uint32_t *x) {
    if (!stack_empty(s)) { // Checks if stack is not empty
        s->top--; // Decrements top indice
        *x = s->items[s->top]; // Stores top of stack into x
        s->items[s->top] = 0; // Sets indice to 0, indicating there is nothing there
        return true;
    }
    return false;
}

// Returns true of false based on iff peak is able to be found, stores peak value in x
bool stack_peek(Stack *s, uint32_t *x) {
    if (!stack_empty(s)) { // Checks if stack is not empty
        *x = s->items[s->top - 1]; // Stores top indice into x
        return true;
    }
    return false;
}

// Copies content from source stack to destination stack
void stack_copy(Stack *dst, Stack *src) {
    for (uint32_t i = 0; i < dst->capacity; i++) {
        dst->items[i] = src->items[i];
    }
    dst->top = src->top;
    return;
}

// Prints out contents of stack to outfile
// Provided by Dr Long
void stack_print(Stack *s, FILE *outfile, char *cities[]) {
    for (uint32_t i = 0; i < s->top; i++) {
        fprintf(outfile, "%s", cities[s->items[i]]);
        if (i + 1 != s->top) {
            fprintf(outfile, " -> ");
        }
    }
    fprintf(outfile, "\n");
}