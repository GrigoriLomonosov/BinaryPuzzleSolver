#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdbool.h>

#include "Node.h"

typedef struct LinkedList{
	Node* first;

}LinkedList;

LinkedList* init_linked_list(Node* first);
void free_linked_list(LinkedList* ll);

/*
Adds a possibility at the beginning of the LinkedList.
*/
void add_node(LinkedList* ll, int* poss, unsigned int* arr_length);

/*
 Returns true if the Node with the array 'poss' was successfully deleted from the LinkedList. False if the LinkedList doesn't contain 
 a Node with the array.
 */
bool remove_node(LinkedList* ll, int* poss);

#endif
