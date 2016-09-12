#ifndef NODE_H
#define NODE_H

#include <stdio.h>
#include <stdlib.h>

//Node in a linked list to keep track of the possibilities in a given row.
typedef struct Node {
	int* arr;
	struct Node *next;
	int* arr_length;
}Node;

Node* init_node(int* arr, Node* next, unsigned int* arr_length);
void free_node(Node* node);

int add_new_next(Node* current, Node* new_next);

void print_node(Node* node);

#endif
