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

/*
The new following node of the current becomes new_next and new_next gets the follower F3 from the follower F2 from current
as new follower. F2 dissapears from the LinkedList and new_next is the new follower of current and has F3 as follower.
*/
void add_new_next(Node* current, Node* new_next);

void print_node(Node* node);

#endif
