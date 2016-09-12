#ifndef NODE_H
#define NODE_H

#include <stdio.h>
#include <stdlib.h>

//Node in a linked list to keep track of the possibilities in a given row.
typedef struct Node {
	int* x;
	struct Node *next;
}Node;

void init_node(int* arr, Node* next);
void free_node(Node* node);

int add_new_next(Node* new_next);

void print_node(Node* node);

#endif
