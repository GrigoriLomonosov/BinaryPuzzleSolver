#ifndef ROWPOSSIBILITIES_H
#define ROWPOSSIBILITIES_H

#include "Node.h"

typedef struct RowPossibilities {
	int* row_number;
	int* number_of_possibilities;
	int* row_length;
	Node* first_node;
}RowPossibilities;

RowPossibilities* init_possibilities(Node* first_node);
void free_possibilities(RowPossibilities* poss);
void print_possibilities(RowPossibilities* poss);

void add_possibilty(RowPossibilities* poss, int* possibility);

int remove_possibility(RowPossibilities* poss, int* possibility);

#endif