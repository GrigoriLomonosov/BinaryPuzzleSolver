#include "BinaryPuzzle.h"

//Checks whether the string only contains 1,0 or -.
bool check_char_in_string(char* input) {
	if (input[0] == '\0') {
		return false;
	}
	else {
		unsigned int i = 0;
		while (i<strlen(input)) {
			if (input[i] != '0' && input[i] != '1' && input[i] != '-') {
				return false;
			}
			i++;
		}
		return true;
	}
}

//Returns an array of all possibilities a row/col can have for a given dimension
int** all_possibilities(int* dim) {
	//The minimal dimension is 6, so the number of possibilities is 2^(dim/2). This is not the correct formula for 2 and 4,
	//but these dimensions should not be possible.
	int** possibilities = malloc(sizeof(int*) * pow(2, *dim/2));
	for (int i = 0; i < dim; i++) {
		possibilities[i] = malloc(sizeof(int*) * *dim);
	}
	//fill with possible combos...
	for (int i = 0; i < *dim; i++) {
		for (int j = 0; j < *dim; j++) {
			//TO DO
		}
	}
}

BinaryPuzzle* init_puzzle(int dim) {
	if (dim % 2 != 0 || dim < MIN_DIMENSION || dim > MAX_DIMENSION) {
		//printf("error: if n is the length of the inputstring, n should be even, >=36 and <= 1296);		
		return NULL;
		//exit(1);
	}
	BinaryPuzzle* puzzle_pointer = malloc(sizeof(BinaryPuzzle));
	if (!puzzle_pointer) {
		printf("ERROR: Allocation failed, insufficient memory for BinaryPuzzle?\n");
		exit(1);
	}

	// Create components
	puzzle_pointer->dim = malloc(sizeof(int));
	puzzle_pointer->squares = calloc(sizeof(int*),dim);
	puzzle_pointer->transponse = calloc(sizeof(int*),dim);
	puzzle_pointer->row_possibilities = calloc(sizeof(RowPossibilities*),dim);
	puzzle_pointer->col_possibilities = calloc(sizeof(RowPossibilities*), dim);

	if (!puzzle_pointer->dim || !puzzle_pointer->squares || !puzzle_pointer->transponse) {
		printf("ERROR: Allocation failed, insufficient memory for BinaryPuzzle?\n");
		exit(1);
	}

	// Initialize components
	*(puzzle_pointer->dim) = dim;

	for (int i = 0; i < dim; i++) {
		puzzle_pointer->squares[i] = calloc(sizeof(int),dim);
		puzzle_pointer->transponse[i] = calloc(sizeof(int),dim);
		puzzle_pointer->row_possibilities[i] = malloc(sizeof(RowPossibilities*));
		puzzle_pointer->col_possibilities[i] = malloc(sizeof(RowPossibilities*));
	}
	// return
	return puzzle_pointer;
}

BinaryPuzzle* init_puzzle_by_pattern(char* input) {
	if (strlen(input) % 2 != 0 || !check_char_in_string(input)) {
		//printf("error: inputstring may only contain '0','1' or '-'\n");		
		return NULL;
		//exit(1);
	}
	else
	{
		int dimension = (int) sqrt(strlen(input));
		BinaryPuzzle* puzzle_pointer = init_puzzle(dimension);
		if (!puzzle_pointer) {
			printf("ERROR: Creation failed\n");
			return NULL;
		}
		for (int i = 0; i < dimension; i++) {
			for (int j = 0; j < dimension; j++) {
				char c = input[i*dimension + j];
				if (c == '-') {
					puzzle_pointer->squares[i][j] = -1;
				}
				else {
					//c can only be 0 (ascii=48) or 1 (ascii=49). -48 to make it an int.
					puzzle_pointer->squares[i][j] = c - 48;
				}
			}
		}
		for (int i = 0; i < dimension; i++) {
			for (int j = 0; j < dimension; j++) {
				puzzle_pointer->transponse[i][j] = puzzle_pointer->squares[j][i];
			}
		}
		return puzzle_pointer;
	}
}

void free_puzzle(BinaryPuzzle* puzzle) {
	for (int i = 0; i < *puzzle->dim; i++) {
		free(puzzle->squares[i]);
		free(puzzle->transponse[i]);
	}
	free(puzzle->squares);
	free(puzzle->transponse);
	free(puzzle->dim);
	free(puzzle);
}

void print_puzzle(BinaryPuzzle* puzzle) {
	for (int i = 0; i < *puzzle->dim; i++) {
		for (int j = 0; j < *puzzle->dim; j++) {
			// print 1,0 or - only
			if(puzzle->squares[i][j]==0 || puzzle->squares[i][j] == 1)
				printf("%d", puzzle->squares[i][j]); 
			else
				printf("%c", '-');
		}
		printf("\n");
	}
	printf("\n");
}

bool hasEmptyCell(BinaryPuzzle* puzzle) {
	for (int i = 0; i < *puzzle->dim; i++) {
		for (int j = 0; j < *puzzle->dim; j++) {
			int value = puzzle->squares[i][j];
			if (value != 0 && value != 1)
				return true; 
		}
	}
	return false;
}

BinaryPuzzle* clone(BinaryPuzzle* puzzle) {
	if (puzzle->squares == NULL ||puzzle ->transponse == NULL || puzzle->dim==NULL)
		return NULL;
	BinaryPuzzle* clone = init_puzzle(*puzzle->dim);
	if (!clone)
		return NULL;
	for (int i = 0; i < *puzzle->dim; i++) {
		for (int j = 0; j < *puzzle->dim; j++) {
			add_number(clone, i, j, puzzle->squares[i][j]);
		}
	}
	return clone;
}

int compare_puzzles(BinaryPuzzle* puzzle_1, BinaryPuzzle* puzzle_2) {
	if (*puzzle_1->dim == *puzzle_2->dim) {
		for (int i = 0; i < *puzzle_1->dim; i++) {
			for (int j = 0; j < *puzzle_1->dim; j++) {
				if (puzzle_1->squares[i][j] != puzzle_2->squares[i][j]) {
					printf("puzzle1: \n");
					print_puzzle(puzzle_1);
					printf("puzzle2: \n");
					print_puzzle(puzzle_2);
					return 1;
				}
			}
		}
		return 0;
	}
	else {
		return 1;
	}
}

/*
Adds a 0 or 1 or '-1' to the given square in the puzzle.
*/
void add_number(BinaryPuzzle* puzzle, int row, int col, int number) {
	if (row < 0 || row > *puzzle->dim || col < 0 || col > *puzzle->dim) {
		printf("ERROR: The given coordinates fall out of scope of the matrix dimensions.");
		exit(1);
	}
	puzzle->squares[row][col] = number;
	puzzle->transponse[col][row] = number;
}

int compare_arrays(int* first, int* second, int size) {
	for (int i = 0; i < size; i++) {
		if (first[i] != second[i]) {
			return 1;			
		}	
	}
	return 0;
}

/*
Returns 0 if and only if a given array is a complete, valid row for the given puzzle.
*/
bool is_valid_row(BinaryPuzzle* puzzle, int* row, int row_number) {
	int count_0 = 0;
	int count_1 = 1;
	for (int i = 0; i < *puzzle->dim; i++) {
		if (row[i] == 0) {
			count_0++;
		}
		if (row[i] == 1) {
			count_1;
		}
		if (row[i] == -1) {
			return false;
		}
		if (i >= 1 && i < *puzzle->dim - 1) {
			if (row[i - 1] == row[i] && row[i] == row[i + 1]) {
				return false;
			}
		}
	}
	if (count_0 != *puzzle->dim / 2 || count_1 != *puzzle->dim / 2) {
		return false;
	}
	//Check for duplicate rows
	for (int k = 0; k < *puzzle->dim; k++) {
		if (compare_arrays(row, puzzle->squares[k], *puzzle->dim) == 0 && row_number != k) {
			return false;
		}
	}
	return true;
}
//
///*
//Returns 0 if and only if a given array is still a possibility for a valid row in the given puzzle.
//*/
//int is_still_possible_row(BinaryPuzzle* puzzle, int* row, int row_number) {
//	int count_0 = 0;
//	int count_1 = 1;
//	for (int i = 0; i < *puzzle->dim; i++) {
//		if (row[i] == 0) {
//			count_0++;
//		}
//		if (row[i] == 1) {
//			count_1;
//		}
//		if (i >= 1 && i < *puzzle->dim - 1) {
//			if (row[i - 1] == row[i] && row[i] == row[i + 1] && row[i] != -1) {
//				return 1;
//			}
//		}
//	}
//	if (count_0 > *puzzle->dim / 2 || count_1 > *puzzle->dim / 2) {
//		return 1;
//	}
//	//Check for duplicate rows
//	for (int k = 0; k < *puzzle->dim; k++) {
//		if (compare_arrays(row, puzzle->squares[k], *puzzle->dim) == 0 && row_number != k && is_valid_row(puzzle,puzzle->squares[k],k) == 0) {
//			return 1;
//		}
//	}
//	return 0;
//}

bool find_pairs(BinaryPuzzle* puzzle) {
	bool changed = false;
	for (int i = 0; i < *puzzle->dim; i++) {
		for (int j = 1; j < *puzzle->dim; j++) {
			//Check row
			if (puzzle->squares[i][j] == puzzle->squares[i][j - 1] && 
				(puzzle->squares[i][j] == 0 || puzzle->squares[i][j] == 1)) {
				//0 becomes 1, 1 becomes 0
				if (j - 2 >= 0 && puzzle->squares[i][j - 2] == -1) {
					add_number(puzzle, i, j - 2, (puzzle->squares[i][j] + 1) % 2);
					changed = true;
				}
				if (j + 1 < *puzzle->dim && puzzle->squares[i][j + 1] == -1) {
					add_number(puzzle, i, j + 1, (puzzle->squares[i][j] + 1) % 2);
					changed = true;
				}
			}
			//Check col
			if (puzzle->transponse[i][j] == puzzle->transponse[i][j -1] &&
				(puzzle->transponse[i][j] == 0 || puzzle->transponse[i][j] == 1)) {
				//0 becomes 1, 1 becomes 0
				if (j - 2 >= 0 && puzzle->transponse[i][j - 2] == -1) {
					add_number(puzzle, j - 2, i, (puzzle->transponse[i][j] + 1) % 2);
					changed = true;
				}
				if (j + 1 < *puzzle->dim && puzzle->transponse[i][j + 1] == -1) {
					add_number(puzzle, j + 1, i, (puzzle->transponse[i][j] + 1) % 2);
					changed = true;
				}
			}
		}
	}
	return changed;
}

bool avoid_trios(BinaryPuzzle* puzzle) {
	bool changed = false;
	for (int i = 0; i < *puzzle->dim; i++) {
		for (int j = 1; j < *puzzle->dim - 1; j++) {
			//Check row
			if (puzzle->squares[i][j] == -1 &&
				puzzle->squares[i][j-1] == puzzle->squares[i][j + 1] &&
				(puzzle->squares[i][j-1] == 0 || puzzle->squares[i][j-1] == 1)) {
				//0 becomes 1, 1 becomes 0
				add_number(puzzle, i, j, (puzzle->squares[i][j-1] + 1) % 2);
				changed = true;
			}
			//Check col
			if (puzzle->transponse[i][j] == -1 &&
				puzzle->transponse[i][j - 1] == puzzle->transponse[i][j + 1] &&
				(puzzle->transponse[i][j - 1] == 0 || puzzle->transponse[i][j - 1] == 1)) {
				//0 becomes 1, 1 becomes 0
				add_number(puzzle, j, i, (puzzle->transponse[i][j - 1] + 1) % 2);
				changed = true;
			}
		}
	}
	return changed;
}

bool complete_array(BinaryPuzzle* puzzle, int* arr, int row_number, bool row) {
	bool changed = false;
	//Check array
	int coordinates[2] = { -1, -1 };
	int count_empty = 0;
	int count_0 = 0;
	int count_1 = 0;
	for (int j = 0; j < *puzzle->dim; j++) {
		if (arr[j] == 0) {
			count_0++;
		}
		if (arr[j] == 1) {
			count_1++;
		}
		if (arr[j] == -1) {
			if (count_empty == 2) {
				break;
			}
			else {
				coordinates[count_empty] = j;
				count_empty++;
			}
		}
	}
	//Switch coordinates when we are working with a column
	int row_1 = row_number;
	int row_2 = row_number;
	int col_1 = coordinates[0];
	int col_2 = coordinates[1];
	if (!row) {
		col_1 = row_number;
		col_2 = row_number;
		row_1 = coordinates[0];
		row_2 = coordinates[1];
	}
	//Change arr
	if (count_0 == *puzzle->dim / 2 && count_empty != 0) {
		if (count_empty == 2) {
			add_number(puzzle, row_1, col_1, 1);
			add_number(puzzle, row_2, col_2, 1);
		}
		else if (count_empty == 1) {
			add_number(puzzle, row_1, col_1, 1);
		}
		changed = true;
	}
	else if (count_1 == *puzzle->dim / 2 && count_empty != 0) {
		if (count_empty == 2) {
			add_number(puzzle, row_1, col_1, 0);
			add_number(puzzle, row_2, col_2, 0);
		}
		else if (count_empty == 1) {
			add_number(puzzle, row_1, col_1, 0);
		}
		changed = true;
	}
	return changed;
}

bool complete_RC(BinaryPuzzle* puzzle) {
	bool result = false;	
	for (int i = 0; i < *puzzle->dim; i++) {
		bool changed_row = complete_array(puzzle, puzzle->squares[i], i, true);
		bool changed_col = complete_array(puzzle, puzzle->transponse[i], i, false);
		if (!result) {
			result = changed_row || changed_col;

		}
	}
	return result;
}

/*
Returns true if the given value can be filled in at the given coordinates.
*/
bool is_number_possible(BinaryPuzzle* puzzle, int row, int col, int value) {
	int opposite_value = (value + 1) % 2;
	if (puzzle->squares[row][col] == -1) {
		add_number(puzzle, row, col, value);
		//Check for 3 consecutive values
		int row_first = col - 1;
		int row_third = col + 1;
		int col_first = row - 1;
		int col_third = row + 1;
		if (row_first >= 0 && row_third < *puzzle->dim && puzzle->squares[row][row_first] == value && puzzle->squares[row][row_third] == value) {
			add_number(puzzle, row, col, -1);
			return false;
		}
		if (col_first >= 0 && col_third < *puzzle->dim && puzzle->transponse[col][col_first] == value && puzzle->transponse[col][col_third] == value) {
			add_number(puzzle, row, col, -1);
			return false;
		}

		int count_empty = 0;
		int count_1 = 0;
		int empty_coordinate = -1;
		int count_empty_C = 0;
		int count_1_C = 0;
		int empty_coordinate_C = -1;
		for (int i = 0; i < *puzzle->dim; i++) {
			if (puzzle->squares[row][i] == -1) {
				count_empty++;
				empty_coordinate = i;
			}
			if (puzzle->squares[row][i] == value) {
				count_1++;
			}
			if (puzzle->transponse[col][i] == -1) {
				count_empty_C++;
				empty_coordinate_C = i;
			}
			if (puzzle->transponse[col][i] == value) {
				count_1_C++;
			}
		}
		//Check number of values
		if (count_1 > *puzzle->dim / 2 || count_1_C > *puzzle->dim / 2) {
			add_number(puzzle, row, col, -1);
			return false;
		}
		//Fill the rows/cols if we assume a value was entered in the given square
		if (count_empty == 1) {
			if (count_1 == *puzzle->dim / 2) {
				add_number(puzzle, row, empty_coordinate, opposite_value);
			}
			else {
				add_number(puzzle, row, empty_coordinate, value);
			}
		}
		if (count_empty_C == 1) {
			if (count_1_C == *puzzle->dim / 2) {
				add_number(puzzle, empty_coordinate_C, col, opposite_value);
			}
			else {
				add_number(puzzle, empty_coordinate_C, col, value);
			}
		}
		//Check for identical rows if the count of empty squares is one or zero
		if (count_empty == 0 || count_empty == 1) {
			for (int k = 0; k < *puzzle->dim; k++) {
				if (compare_arrays(puzzle->squares[row], puzzle->squares[k], *puzzle->dim) == 0 && k != row) {
					add_number(puzzle, row, col, -1);
					if (count_empty == 1) {
						add_number(puzzle, row, empty_coordinate, -1);
					}
					return false;
				}
			}
		}
		//Check for identical cols if the count of empty squares is one or zero.
		if (count_empty_C == 0 || count_empty_C == 1) {
			for (int k = 0; k < *puzzle->dim; k++) {
				if (compare_arrays(puzzle->transponse[col], puzzle->transponse[k], *puzzle->dim) == 0 && k != col) {
					add_number(puzzle, row, col, -1);
					if (count_empty_C == 1) {
						add_number(puzzle, empty_coordinate_C, col, -1);
					}
					return false;
				}
			}
		}
		//Reset the values if value is possible
		add_number(puzzle, row, col, -1);
		if (count_empty == 1) {
			add_number(puzzle, row, empty_coordinate, -1);
		}
		if (count_empty_C == 1) {
			add_number(puzzle, empty_coordinate_C, col, -1);
		}
		return true;
	}
	else {
		return false;
	}
}

bool eliminate_impossible_combos(BinaryPuzzle* puzzle) {
	bool changed = false;
	for (int i = 0; i < *puzzle->dim; i++) {
		for (int j = 0; j < *puzzle->dim; j++) {
			//printf("%b", is_number_possible(puzzle, i, j, 1));
			if (!is_number_possible(puzzle, i, j, 1) && puzzle->squares[i][j] == -1) {
				add_number(puzzle, i, j, 0);
				changed = true;
			}
			if (!is_number_possible(puzzle, i, j, 0) && puzzle->squares[i][j] == -1) {
				add_number(puzzle, i, j, 1);
				changed = true;
			}
		}
	}
	return changed;
}

/*Checks whether a number can be placed at a given index in a pattern of consecutive empty squares, with a given
number of remaining numbers. If this is not possible, the opposite value is entered.
Returns 0 if and only if a number was filled in.
*/
bool check_poss(BinaryPuzzle* puzzle, int length_interval, int remaining, int index, int row_number, int opposite_value) {
	bool changed = false;
	for (int k = 0; k < length_interval; k++) {
		//links = k, rechts = interval - k - 1 voor fictief geplaatste getal
		if ((length_interval - k - 1) / 3 > remaining - 1 || k / 3 > remaining - 1) {
			add_number(puzzle, row_number, k + index, opposite_value);
			changed = true;
		}
	}
	return changed;
}

bool complete_pattern(BinaryPuzzle* puzzle, int* arr, int row_number, bool row) {
	bool changed = false;
	int start_index = 0;
	int pattern_length = 0;
	int max_pattern_length = 0;
	int max_pattern_start_index = 0;
	int number_used_0 = 0;
	int number_used_1 = 0;
	for (int j = 0; j < *puzzle->dim; j++) {
		if (arr[j] == 0) {
			number_used_0++;
			pattern_length = 0;
			start_index = j + 1;
		}
		if (arr[j] == 1) {
			number_used_1++;
			pattern_length = 0;
			start_index = j + 1;
		}
		if (arr[j] == -1) {
			pattern_length++;
			if (pattern_length > max_pattern_length) {
				max_pattern_length = pattern_length;
				max_pattern_start_index = start_index;
			}
		}
	}
	//Change arr if needed
	if (max_pattern_length > 2 && number_used_0 != number_used_1) {
		//Try to fill the pattern with the number that was used the most, as there are fewer possibilities left.
		int opposite_value = 1;
		int value = 0;
		int used = number_used_0;
		if (number_used_1 > number_used_0) {
			opposite_value = 0;
			value = 1;
			used = number_used_1;
		}
		//Followed and preceded by opposite_value
		if (max_pattern_start_index > 0
			&& max_pattern_start_index + max_pattern_length < *puzzle->dim - 1
			&& arr[max_pattern_start_index - 1] == opposite_value
			&& arr[max_pattern_start_index + max_pattern_length] == opposite_value) {
			if (max_pattern_length == 3) {
				printf("2 kanten lengte 3\n");
				if (*puzzle->dim / 2 - used == 1) {
					if (row) {
						add_number(puzzle, row_number, max_pattern_start_index, opposite_value);
						add_number(puzzle, row_number, max_pattern_start_index + 1, value);
						add_number(puzzle, row_number, max_pattern_start_index + 2, opposite_value);
					}
					else {
						add_number(puzzle, max_pattern_start_index, row_number, opposite_value);
						add_number(puzzle, max_pattern_start_index + 1, row_number, value);
						add_number(puzzle, max_pattern_start_index + 2, row_number, opposite_value);
					}
					changed = true;
				}
			}
			else {
				printf("2 kanten lengte >3\n");
				used += 2;
				max_pattern_start_index += 2;
				max_pattern_length -= 4;
				if (row) {
					changed = check_poss(puzzle, max_pattern_length, *puzzle->dim / 2 - used, max_pattern_start_index, row_number, opposite_value) || changed;
				}
				else {
					changed = check_poss(puzzle, max_pattern_length, *puzzle->dim / 2 - used, row_number, max_pattern_start_index, opposite_value) || changed;
				}
			}
		}
		//Preceded by opposite_value
		else if (max_pattern_start_index > 0 && arr[max_pattern_start_index - 1] == opposite_value) {
			if (max_pattern_length == 3) {
				printf("preceeded lengte 3\n");
				if (*puzzle->dim / 2 - used == 1) {
					if (row) {
						add_number(puzzle, row_number, max_pattern_start_index + 2, opposite_value);
					}
					else {
						add_number(puzzle, max_pattern_start_index + 2, row_number, opposite_value);
					}
					changed = true;
				}
			}
			else {
				printf("preceeded lengte >3\n");
				used += 1;
				if ((max_pattern_length - 1) / 3 > *puzzle->dim / 2 - used) {
					if (row) {
						add_number(puzzle, row_number, max_pattern_start_index, opposite_value);
					}
					else {
						add_number(puzzle, max_pattern_start_index, row_number, opposite_value);
					}
					changed = true;
				}
				max_pattern_start_index += 2;
				max_pattern_length -= 2;
				if (row) {
					changed = check_poss(puzzle, max_pattern_length, *puzzle->dim / 2 - used, max_pattern_start_index, row_number, opposite_value) || changed;
				}
				else {
					changed = check_poss(puzzle, max_pattern_length, *puzzle->dim / 2 - used, row_number, max_pattern_start_index, opposite_value) || changed;
				}
			}
		}
		//Followed by opposite_value
		else if (max_pattern_start_index < *puzzle->dim - 1 && arr[max_pattern_start_index + max_pattern_length] == opposite_value) {
			if (max_pattern_length == 3) {
				printf("followed lengte 3\n");
				if (*puzzle->dim / 2 - used == 1) {
					if (row) {
						add_number(puzzle, row_number, max_pattern_start_index, opposite_value);
					}
					else {
						add_number(puzzle, max_pattern_start_index, row_number, opposite_value);
					}
					changed = true;
				}
			}
			else {
				printf("followed lengte >3\n");
				used += 1;
				if ((max_pattern_length - 1) / 3 > *puzzle->dim / 2 - used) {
					if (row) {
						add_number(puzzle, row_number, max_pattern_start_index + max_pattern_length - 1, opposite_value);
					}
					else {
						add_number(puzzle, max_pattern_start_index + max_pattern_length - 1, row_number, opposite_value);
					}
					changed = true;
				}
				max_pattern_length -= 2;
				if (row) {
					changed = check_poss(puzzle, max_pattern_length, *puzzle->dim / 2 - used, max_pattern_start_index, row_number, opposite_value) || changed;
				}
				else {
					changed = check_poss(puzzle, max_pattern_length, *puzzle->dim / 2 - used, row_number, max_pattern_start_index, opposite_value) || changed;
				}
			}
		}
		//Not followed or preceded by opposite_value
		else {
			printf("not proceeded followed\n");
			printf("values: %d, %d, %d \n", max_pattern_length, *puzzle->dim / 2 - used, max_pattern_start_index);
			if (row) {
				changed = check_poss(puzzle, max_pattern_length, *puzzle->dim / 2 - used, max_pattern_start_index, row_number, opposite_value) || changed;
			}
			else {
				changed = check_poss(puzzle, max_pattern_length, *puzzle->dim / 2 - used, row_number, max_pattern_start_index, opposite_value) || changed;
			}
		}
	}
	return changed;
}

bool complete_pattern_RC(BinaryPuzzle* puzzle) {
	bool changed = false;
	for (int i = 0; i < *puzzle->dim; i++) {
		bool changed_row = complete_pattern(puzzle, puzzle->squares[i], i, true);
		bool changed_col = complete_pattern(puzzle, puzzle->transponse[i], i, false);
		if (!changed) {
			changed = changed_row || changed_col;
		}
	}
	return changed;
}

bool eliminate_other_impossible_combos(BinaryPuzzle* puzzle) {
	bool changed = false;
	//TO DO
	return changed;
}

void solve_puzzle(BinaryPuzzle** original) {
	//Werken met een kopie om onverwachte, externe veranderingen te vermijden.
	BinaryPuzzle* puzzle = clone(*original);
	if (!puzzle)
		return;
	// With every iteration we expect to fill in atleast 1 (empty) cell. 
	int maxIter = *puzzle->dim * *puzzle->dim, counter=0;
	// If nothing changed, then all functions return 1; resulting in the sum of n ones = n 
	bool changed = true;
	// CAN BE OPTIMIZED : mogelijke verbetering-> Zo ver mogelijk gaan per vakje, ttz depth first van alle mogelijkheden.
	while ( changed && counter<maxIter ) {
		//Cheap functions
		changed = !(find_pairs(puzzle) && avoid_trios(puzzle) && complete_RC(puzzle));
		if (!changed) {
			// More expensive functions
			changed = !(eliminate_impossible_combos(puzzle) && eliminate_other_impossible_combos(puzzle));
		}
		counter++;
		print_puzzle(puzzle);
	}
	//
	free(*original);
	*original = puzzle;
}