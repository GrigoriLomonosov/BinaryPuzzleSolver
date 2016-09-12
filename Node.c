
#include "Node.h"

Node* init_node(int* arr, Node* next, unsigned int arr_length) {
	Node* node = malloc(sizeof(Node));
	if (!node) {
		printf("ERROR: Allocation failed, insufficient memory for Node?\n");
		exit(1);
	}
	// Create components
	node->arr = malloc(sizeof(int) * arr_length);
	node->next = malloc(sizeof(Node*));
	node->arr_length = malloc(sizeof(int*));
	if ( !node->arr || !node->next || !node->arr_length ) {
		printf("ERROR: Allocation failed, insufficient memory for Node?\n");
		exit(1);
	}
	// Initialize components
	*node->arr = arr;
	*node->arr_length = arr_length;
	*node->next = *next;
	return node;
}

void free_node(Node* node) {
	free(node->arr);
	free(node->arr_length);
	free(node->next);
	free(node);
}

int add_new_next(Node* current, Node* new_next) {
	new_next->next = (current->next)->next;
	free_node(current->next);
	current->next = new_next;
}

void print_node(Node* node) {
	printf("Below see the array this node.\n");
	for (int i = 0; i < node->arr_length; i++) {
		printf("%d", node->arr[i]);
	}
	if (node->next != NULL) {
		printf("The node is not the last element in the linked list.");
	}
	else {
		printf("The node is the last element in the linked list.");
	}
}