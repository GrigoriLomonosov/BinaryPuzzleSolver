#include "RowPossibilities.h"

RowPossibilities* init_possibilities(Node* first_node, int* number_of_poss, int* row_number, int* row_length) {
	RowPossibilities* poss = malloc(sizeof(RowPossibilities));
	if (!poss) {
		printf("ERROR: Allocation failed, insufficient memory for RowPossibilities?\n");
		exit(1);
	}
	// Create components
	poss->first_node = malloc(sizeof(Node*));
	poss->number_of_possibilities = malloc(sizeof(int*));
	poss->row_length = malloc(sizeof(int*));
	poss->row_number = malloc(sizeof(int*));
	if (!poss->first_node || !poss->number_of_possibilities || !poss->row_length || !poss->row_number) {
		printf("ERROR: Allocation failed, insufficient memory for RowPossibilities?\n");
		exit(1);
	}
	// Initialize components
	poss->first_node = first_node;
	poss->number_of_possibilities = number_of_poss;
	poss->row_number = row_number;
	poss->row_length = row_length;
	return poss;
}

void free_possibilities(RowPossibilities* poss) {
	free_node(poss->first_node);
	free(poss->number_of_possibilities);
	free(poss->row_length);
	free(poss->row_number);
	free(poss);
}

void print_possibilities(RowPossibilities* poss) {
	printf("Number of possibilities: %d.\n", *poss->number_of_possibilities);
	printf("Row number: %d.\n", *poss->row_number);
	printf("Row length: %d.\n", *poss->row_length);
	Node* node = poss->first_node;
	while (node != NULL) {
		for (int i = 0; i < *node->arr_length; i++) {
			printf("%d", node->arr[i]);
		}
		printf("\n");
		node = node->next;
	}
}

void add_possibilty(RowPossibilities* poss, int* possibility) {
	Node* new_node = init_node(possibility, poss->first_node, poss->row_length);
}

int remove_possibility(RowPossibilities* poss, int* possibility) {
	Node* previous = poss->first_node;
	Node* node = poss->first_node;
	int found = 1;
	while (node != NULL) {
		int count = 0;
		for (int j = 0; j < *poss->row_length; j++) {
			if (possibility[j] != node->arr[j]) {
				previous = node;
				node = node->next;
				break;
			}
			else {
				count++;
			}
		}
		if (count == *poss->row_length) {
			previous->next = node->next;
			free_node(node);
			found = 0;
			break;
		}
	}
	return found;
}