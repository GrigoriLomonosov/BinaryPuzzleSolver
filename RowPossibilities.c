#include "RowPossibilities.h"

RowPossibilities* init_possibilities(LinkedList* ll, int* number_of_poss, int* row_number) {
	RowPossibilities* poss = malloc(sizeof(RowPossibilities));
	if (!poss) {
		printf("ERROR: Allocation failed, insufficient memory for RowPossibilities?\n");
		exit(1);
	}
	// Create components
	LinkedList* list = malloc(sizeof(LinkedList));
	poss->number_of_possibilities = malloc(sizeof(int*));
	poss->row_number = malloc(sizeof(int*));
	if (list || !poss->number_of_possibilities || !poss->row_number) {
		printf("ERROR: Allocation failed, insufficient memory for RowPossibilities?\n");
		exit(1);
	}
	// Initialize components
	poss->ll = ll;
	poss->number_of_possibilities = number_of_poss;
	poss->row_number = row_number;
	return poss;
}

void free_possibilities(RowPossibilities* poss) {
	free_linked_list(poss->ll);
	free(poss->number_of_possibilities);
	free(poss->row_number);
	free(poss);
}

void print_possibilities(RowPossibilities* poss) {
	printf("Number of possibilities: %d.\n", *poss->number_of_possibilities);
	printf("Row number: %d.\n", *poss->row_number);
	Node* node = poss->ll->first;
	while (node != NULL) {
		for (int i = 0; i < *node->arr_length; i++) {
			printf("%d", node->arr[i]);
		}
		printf("\n");
		node = node->next;
	}
}

void add_possibilty(RowPossibilities* poss, int* possibility, unsigned int* arr_length) {
	//Adds to linkedlist
	add_node(poss->ll, possibility, arr_length);
	poss->number_of_possibilities++;
}

bool remove_possibility(RowPossibilities* poss, int* possibility) {
	//Removes from linkedlist
	if (remove_node(poss->ll, possibility)) {
		poss->number_of_possibilities--;
		return true;
	}
	else {
		return false;
	}
}