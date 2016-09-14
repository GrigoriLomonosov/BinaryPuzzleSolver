
#include "LinkedList.h"

LinkedList* init_linked_list(Node* first) {
	LinkedList* ll = malloc(sizeof(LinkedList));
	ll->first = malloc(sizeof(Node*));
	if (!ll || !ll->first) {
		printf("ERROR: Allocation failed, insufficient memory for LinkedList?\n");
		exit(1);
	}
	ll->first = first;
	return ll;
}

void free_linked_list(LinkedList* ll) {
	Node* first = ll->first;
	Node* next = ll->first->next;
	while (next != NULL) {
		free_node(first);
		first = next;
		next = next->next;
	}
	free(ll);
}

void add_node(LinkedList* ll, int* poss, unsigned int* arr_length) {
	Node* new_node = init_node(poss, ll->first, arr_length);
}

bool remove_node(LinkedList* ll, int* poss){
	bool removed = false;
	Node* previous = ll->first;
	Node* node = ll->first;
	while (node != NULL) {
		int count = 0;
		for (int j = 0; j < *previous->arr_length; j++) {
			if (previous->arr[j] != poss[j]) {
				previous = node;
				node = node->next;
				break;
			}
			else {
				count++;
			}
		}
		if (count == *previous->arr_length) {
			previous->next = node->next;
			free_node(node);
			removed = true;
			break;
		}
	}
	return removed;
}