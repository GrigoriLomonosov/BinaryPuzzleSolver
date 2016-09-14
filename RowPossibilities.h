#ifndef ROWPOSSIBILITIES_H
#define ROWPOSSIBILITIES_H

#include "LinkedList.h"

typedef struct RowPossibilities {
	int* row_number;
	int* number_of_possibilities;
	LinkedList* ll;
}RowPossibilities;

RowPossibilities* init_possibilities(LinkedList* ll, int* number_of_poss, int* row_number);
void free_possibilities(RowPossibilities* poss);
void print_possibilities(RowPossibilities* poss);

void add_possibilty(RowPossibilities* poss, int* possibility, unsigned int* arr_length);

bool remove_possibility(RowPossibilities* poss, int* possibility);

#endif