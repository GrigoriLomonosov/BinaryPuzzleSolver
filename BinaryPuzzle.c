#include "BinaryPuzzle.h"

//Checks whether the string only contains 1,0 or -.
int check_char_in_string(char* input) {
	if (input[0] == '\0') {
		return 1;
	}
	else {
		unsigned int i = 0;
		while (i<strlen(input)) {
			if (input[i] != '0' && input[i] != '1' && input[i] != '-') {
				return 1;
			}
			i++;
		}
		return 0;
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

	if (!puzzle_pointer->dim || !puzzle_pointer->squares || !puzzle_pointer->transponse) {
		printf("ERROR: Allocation failed, insufficient memory for BinaryPuzzle?\n");
		exit(1);
	}

	// Initialize components
	*(puzzle_pointer->dim) = dim;

	for (int i = 0; i < dim; i++) {
		puzzle_pointer->squares[i] = calloc(sizeof(int),dim);
		puzzle_pointer->transponse[i] = calloc(sizeof(int),dim);
	}
	// return
	return puzzle_pointer;
}

BinaryPuzzle* init_puzzle_by_pattern(char* input) {
	if (strlen(input) % 2 != 0 ||check_char_in_string(input) != 0) {
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
		if (puzzle->squares[i])
			free(puzzle->squares[i]);
		if(puzzle->transponse[i])
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
	//printf("row: %d col: %d nr: %d", row, col, number);
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
int is_valid_row(BinaryPuzzle* puzzle, int* row, int row_number) {
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
			return 1;
		}
		if (i >= 1 && i < *puzzle->dim - 1) {
			if (row[i - 1] == row[i] && row[i] == row[i + 1]) {
				return 1;
			}
		}
	}
	if (count_0 != *puzzle->dim / 2 || count_1 != *puzzle->dim / 2) {
		return 1;
	}
	//Check for duplicate rows
	for (int k = 0; k < *puzzle->dim; k++) {
		if (compare_arrays(row, puzzle->squares[k], *puzzle->dim) == 0 && row_number != k) {
			return 1;
		}
	}
	return 0;
}

/*
Returns 0 if and only if a given array is still a possibility for a valid row in the given puzzle.
*/
int is_still_possible_row(BinaryPuzzle* puzzle, int* row, int row_number) {
	int count_0 = 0;
	int count_1 = 1;
	for (int i = 0; i < *puzzle->dim; i++) {
		if (row[i] == 0) {
			count_0++;
		}
		if (row[i] == 1) {
			count_1;
		}
		if (i >= 1 && i < *puzzle->dim - 1) {
			if (row[i - 1] == row[i] && row[i] == row[i + 1] && row[i] != -1) {
				return 1;
			}
		}
	}
	if (count_0 > *puzzle->dim / 2 || count_1 > *puzzle->dim / 2) {
		return 1;
	}
	//Check for duplicate rows
	for (int k = 0; k < *puzzle->dim; k++) {
		if (compare_arrays(row, puzzle->squares[k], *puzzle->dim) == 0 && row_number != k && is_valid_row(puzzle,puzzle->squares[k],k) == 0) {
			return 1;
		}
	}
	return 0;
}

int find_pairs(BinaryPuzzle* puzzle) {
	int changed = 1;
	for (int i = 0; i < *puzzle->dim; i++) {
		for (int j = 1; j < *puzzle->dim; j++) {
			//Check row
			if (puzzle->squares[i][j] == puzzle->squares[i][j - 1] && 
				(puzzle->squares[i][j] == 0 || puzzle->squares[i][j] == 1)) {
				//0 becomes 1, 1 becomes 0
				if (j - 2 >= 0 && puzzle->squares[i][j - 2] == -1) {
					add_number(puzzle, i, j - 2, (puzzle->squares[i][j] + 1) % 2);
					changed = 0;
				}
				if (j + 1 < *puzzle->dim && puzzle->squares[i][j + 1] == -1) {
					add_number(puzzle, i, j + 1, (puzzle->squares[i][j] + 1) % 2);
					changed = 0;
				}
			}
			//Check col
			if (puzzle->transponse[i][j] == puzzle->transponse[i][j -1] &&
				(puzzle->transponse[i][j] == 0 || puzzle->transponse[i][j] == 1)) {
				//0 becomes 1, 1 becomes 0
				if (j - 2 >= 0 && puzzle->transponse[i][j - 2] == -1) {
					add_number(puzzle, j - 2, i, (puzzle->transponse[i][j] + 1) % 2);
					changed = 0;
				}
				if (j + 1 < *puzzle->dim && puzzle->transponse[i][j + 1] == -1) {
					add_number(puzzle, j + 1, i, (puzzle->transponse[i][j] + 1) % 2);
					changed = 0;
				}
			}
		}
	}
	return changed;
}

int avoid_trios(BinaryPuzzle* puzzle) {
	int changed = 1;
	for (int i = 0; i < *puzzle->dim; i++) {
		for (int j = 1; j < *puzzle->dim - 1; j++) {
			//Check row
			if (puzzle->squares[i][j] == -1 &&
				puzzle->squares[i][j-1] == puzzle->squares[i][j + 1] &&
				(puzzle->squares[i][j-1] == 0 || puzzle->squares[i][j-1] == 1)) {
				//0 becomes 1, 1 becomes 0
				add_number(puzzle, i, j, (puzzle->squares[i][j-1] + 1) % 2);
				changed = 0;
			}
			//Check col
			if (puzzle->transponse[i][j] == -1 &&
				puzzle->transponse[i][j - 1] == puzzle->transponse[i][j + 1] &&
				(puzzle->transponse[i][j - 1] == 0 || puzzle->transponse[i][j - 1] == 1)) {
				//0 becomes 1, 1 becomes 0
				add_number(puzzle, j, i, (puzzle->transponse[i][j - 1] + 1) % 2);
				changed = 0;
			}
		}
	}
	return changed;
}

int complete_RC(BinaryPuzzle* puzzle) {
	int changed = 1;	
	for (int i = 0; i < *puzzle->dim; i++) {
		//Check row
		int coordinates[2] = { -1, -1 };
		int count_empty = 0;
		int count_0 = 0;
		int count_1 = 0;
		for (int j = 0; j < *puzzle->dim; j++) {
			if (puzzle->squares[i][j] == 0) {
				count_0++;
			}
			if (puzzle->squares[i][j] == 1) {
				count_1++;
			}
			if (puzzle->squares[i][j] == -1) {
				if (count_empty == 2) {
					break;
				}
				else {
					coordinates[count_empty] = j;
					count_empty++;
				}
			}
		}
		//Change row
		if (count_0 == *puzzle->dim / 2) {
			if (count_empty == 2) {
				add_number(puzzle, i, coordinates[0], 1);
				add_number(puzzle, i, coordinates[1], 1);
			}
			else if (count_empty == 1) {
				add_number(puzzle, i, coordinates[0], 1);
			}
			changed = 0;
		}
		else if (count_1 == *puzzle->dim / 2) {
			if (count_empty == 2) {
				add_number(puzzle, i, coordinates[0], 0);
				add_number(puzzle, i, coordinates[1], 0);
			}
			else if (count_empty == 1) {
				add_number(puzzle, i, coordinates[0], 0);
			}
			changed = 0;
		}
		//Check col
		int coordinates_C[2] = { -1, -1 };
		int count_empty_C = 0;
		int count_0_C = 0;
		int count_1_C = 0;
		for (int j = 0; j < *puzzle->dim; j++) {
			if (puzzle->transponse[i][j] == 0) {
				count_0_C++;
			}
			if (puzzle->transponse[i][j] == 1) {
				count_1_C++;
			}
			if (puzzle->transponse[i][j] == -1) {
				if (count_empty_C == 2) {
					break;
				}
				else {
					coordinates_C[count_empty_C] = j;
					count_empty_C++;
				}
			}
		}
		//Change col
		if (count_0_C == *puzzle->dim / 2) {
			if (count_empty_C == 2) {
				add_number(puzzle, coordinates_C[0], i, 1);
				add_number(puzzle, coordinates_C[1], i, 1);
			}
			else if (count_empty_C == 1) {
				add_number(puzzle, coordinates_C[0], i, 1);
			}
			changed = 0;
		}
		else if (count_1_C == *puzzle->dim / 2) {
			if (count_empty_C == 2) {
				add_number(puzzle, coordinates_C[0], i, 0);
				add_number(puzzle, coordinates_C[1], i, 0);
			}
			else if (count_empty_C == 1) {
				add_number(puzzle, coordinates_C[0], i, 0);
			}
			changed = 0;
		}
	}
	return changed;
}

/*
Returns 0 if and only if a 1 can be filled in in the given square
based on the three rules of binary puzzles.
*/
//NIETS VERVANGEN DOOR is_still_possible row. DIT GAAT VERTRAGEN!!
int is_one_possible(BinaryPuzzle* puzzle, int row, int col){
	if (puzzle->squares[row][col] == -1) {
		add_number(puzzle, row, col, 1);
		//Check for 3 consecutive ones
		int row_first = col - 1;
		int row_third = col + 1;
		int col_first = row - 1;
		int col_third = row + 1;
		if (row_first >= 0 && row_third < *puzzle->dim && puzzle->squares[row][row_first] == 1 && puzzle->squares[row][row_third] == 1) {
			add_number(puzzle, row, col, -1);
			return 1;
		}
		if (col_first >= 0 && col_third < *puzzle->dim && puzzle->transponse[col][col_first] == 1 && puzzle->transponse[col][col_third] == 1) {
			add_number(puzzle, row, col, -1);
			return 1;
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
			if (puzzle->squares[row][i] == 1) {
				count_1++;
			}
			if (puzzle->transponse[col][i] == -1) {
				count_empty_C++;
				empty_coordinate_C = i;
			}
			if (puzzle->transponse[col][i] == 1) {
				count_1_C++;
			}
		}
		//Check number of ones
		if (count_1 > *puzzle->dim / 2 || count_1_C > *puzzle->dim / 2) {
			add_number(puzzle, row, col, -1);
			return 1;
		}
		//Fill the rows/cols if we assume a 1 was entered in the given square
		if (count_empty == 1) {
			if (count_1 == *puzzle->dim / 2) {
				add_number(puzzle, row, empty_coordinate, 0);
			}
			else {
				add_number(puzzle, row, empty_coordinate, 1);
			}
		}
		if (count_empty_C == 1) {
			if (count_1_C == *puzzle->dim / 2) {
				add_number(puzzle, empty_coordinate_C, col, 0);
			}
			else {
				add_number(puzzle, empty_coordinate_C, col, 1);
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
					return 1;
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
					return 1;
				}
			}
		}
		//Reset the values if 1 is possible
		add_number(puzzle, row, col, -1);
		if (count_empty == 1) {
			add_number(puzzle, row, empty_coordinate, -1);
			}
		if (count_empty_C == 1) {
			add_number(puzzle, empty_coordinate_C, col, -1);
		}
	return 0;
}
	else {
		return 1;
	}
}

/*
Returns 0 if and only if a 0 can be filled in in the given square
based on the three rules of binary puzzles.
*/
//NIETS VERVANGEN DOOR is_still_possible row. DIT GAAT VERTRAGEN!!
int is_zero_possible(BinaryPuzzle*puzzle, int row, int col) {
	if (puzzle->squares[row][col] == -1) {
		add_number(puzzle, row, col, 0);
		//Check for 3 consecutive zeros
		int row_first = col - 1;
		int row_third = col + 1;
		int col_first = row - 1;
		int col_third = row + 1;
		if (row_first >= 0 && row_third < *puzzle->dim && puzzle->squares[row][row_first] == 0 && puzzle->squares[row][row_third] == 0) {
			add_number(puzzle, row, col, -1);
			return 1;
		}
		if (col_first >= 0 && col_third < *puzzle->dim && puzzle->transponse[col][col_first] == 0 && puzzle->transponse[col][col_third] == 0) {
			add_number(puzzle, row, col, -1);
			return 1;
		}

		int count_empty = 0;
		int count_0 = 0;
		int empty_coordinate = -1;
		int count_empty_C = 0;
		int count_0_C = 0;
		int empty_coordinate_C = -1;
		for (int i = 0; i < *puzzle->dim; i++) {
			if (puzzle->squares[row][i] == -1) {
				count_empty++;
				empty_coordinate = i;
			}
			if (puzzle->squares[row][i] == 0) {
				count_0++;
			}
			if (puzzle->transponse[col][i] == -1) {
				count_empty_C++;
				empty_coordinate_C = i;
			}
			if (puzzle->transponse[col][i] == 0) {
				count_0_C++;
			}
		}
		//Check number of zeros
		if (count_0 > *puzzle->dim / 2 || count_0_C > *puzzle->dim / 2) {
			add_number(puzzle, row, col, -1);
			return 1;
		}
		//Fill the rows/cols if we assume a 0 was entered in the given square
		if (count_empty == 1) {
			if (count_0 == *puzzle->dim / 2) {
				add_number(puzzle, row, empty_coordinate, 1);
			}
			else {
				add_number(puzzle, row, empty_coordinate, 0);
			}
		}
		if (count_empty_C == 1) {
			if (count_0_C == *puzzle->dim / 2) {
				add_number(puzzle, empty_coordinate_C, col, 1);
			}
			else {
				add_number(puzzle, empty_coordinate_C, col, 0);
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
					return 1;
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
					return 1;
				}
			}
		}
		//Reset the values if 0 is possible
		add_number(puzzle, row, col, -1);
		if (count_empty == 1) {
			add_number(puzzle, row, empty_coordinate, -1);
		}
		if (count_empty_C == 1) {
			add_number(puzzle, empty_coordinate_C, col, -1);
		}
		return 0;
	}
	else {
		return 1;
	}
}

int eliminate_impossible_combos(BinaryPuzzle* puzzle) {
	int changed = 1;
	for (int i = 0; i < *puzzle->dim; i++) {
		for (int j = 0; j < *puzzle->dim; j++) {
			if (is_one_possible(puzzle, i, j) != 0 && puzzle->squares[i][j] == -1) {
				add_number(puzzle, i, j, 0);
				changed = 0;
			}
			if (is_zero_possible(puzzle, i, j) != 0 && puzzle->squares[i][j] == -1) {
				add_number(puzzle, i, j, 1);
				changed = 0;
			}
		}
	}
	return changed;
}

/*Checks whether a number can be placed at a given index in a pattern of consecutive empty squares, with a given
number of remaining numbers. If this is not possible, the opposite value is entered.
Returns 0 if and only if a number was filled in.
*/
//int check_poss(int length_interval, int remaining, int index) {
//	return (length_interval-index) / 3 <= remaining && index / 3 <= remaining;
//}
int check_poss(BinaryPuzzle* puzzle, int length_interval, int remaining, int index, int row_number, int opposite_value) {
	int changed = 1;
	for (int k = 0; k < length_interval; k++) {
		if ((length_interval - k) / 3 > remaining || k / 3 > remaining) {
			add_number(puzzle, row_number, k + index, opposite_value);
			changed = 0;
		}
	}
	return changed;
}

int complete_half_RC(BinaryPuzzle* puzzle) {
	int changed = 1;
	for (int i = 0; i < *puzzle->dim; i++) {
		//Variables for row
		int start_index = 0;
		int pattern_length = 0;
		int max_pattern_length = 0;
		int max_pattern_start_index = 0;
		int number_used_0 = 0;
		int number_used_1 = 0;
		//Variables for col

		for (int j = 0; j < *puzzle->dim; j++) {
			if (puzzle->squares[i][j] == 0) {
				number_used_0++;
				pattern_length = 0;
				start_index = j + 1;
			}
			if (puzzle->squares[i][j] == 1) {
				number_used_1++;
				pattern_length = 0;
				start_index = j + 1;
			}
			if (puzzle->squares[i][j] == -1) {
				pattern_length++;
				if (pattern_length > max_pattern_length) {
					max_pattern_length = pattern_length;
					max_pattern_start_index = start_index;
				}
			}
		}
		printf("pattern_length: %d, startindex: %d, gebruikte0: %d, gebruikte1: %d\n", max_pattern_length, max_pattern_start_index, number_used_0, number_used_1);
		
		//Try to fill the pattern with the number that was used the most, as there are fewer possibilities left.
		if (number_used_1 > number_used_0 && max_pattern_length > 2) {
			//Followed and preceded by zero
			if (max_pattern_start_index > 0
				&& max_pattern_start_index + max_pattern_length < *puzzle->dim - 1
				&& puzzle->squares[i][max_pattern_start_index - 1] == 0
				&& puzzle->squares[i][max_pattern_start_index + max_pattern_length - 1] == 0) {
				if (max_pattern_length == 3) {
					if (*puzzle->dim / 2 - number_used_1 == 1) {
						add_number(puzzle, i, max_pattern_start_index, 0);
						add_number(puzzle, i, max_pattern_start_index + 1, 1);
						add_number(puzzle, i, max_pattern_start_index + 2, 0);
					}
				}
				else {
					max_pattern_start_index += 2;
					number_used_1 += 2;
					max_pattern_length -= 4;
					changed = check_poss(puzzle, max_pattern_length, *puzzle->dim / 2 - number_used_1, max_pattern_start_index, i, 0);
				}
			}
			//Preceded by zero
			else if (max_pattern_start_index > 0 && puzzle->squares[i][max_pattern_start_index - 1] == 0) {
				if (max_pattern_length == 3) {
					if (*puzzle->dim / 2 - number_used_1 == 1) {
						add_number(puzzle, i, max_pattern_start_index + 2, 0);
						changed = 0;
					}
				}
				else {
					max_pattern_start_index += 2;
					number_used_1 += 1;
					max_pattern_length -= 2;
					changed = check_poss(puzzle, max_pattern_length, *puzzle->dim / 2 - number_used_1, max_pattern_start_index, i, 0);
				}
			}
			//Followed by zero
			else if (max_pattern_start_index < *puzzle->dim - 1 && puzzle->squares[i][max_pattern_start_index - 1] == 0) {
				if (max_pattern_length == 3) {
					if (*puzzle->dim / 2 - number_used_1 == 1) {
						add_number(puzzle, i, max_pattern_start_index, 0);
						changed = 0;
					}
				}
				else {
					number_used_1 += 1;
					max_pattern_length -= 2;
					changed = check_poss(puzzle, max_pattern_length, *puzzle->dim / 2 - number_used_1, max_pattern_start_index, i, 0);
				}
			}
			//Not followed or preceded by zero
			else {
				changed = check_poss(puzzle, max_pattern_length, *puzzle->dim / 2 - number_used_1, max_pattern_start_index, i, 0);
			}
		}
		



		else if (number_used_1 < number_used_0) {

		}

		//Check if pattern is preceded or followed by the opposite number

		//int first_half_0 = 0;
		//int second_half_0 = 0;
		//int first_half_1 = 0;
		//int second_half_1 = 0;
		//int first_half_0_C = 0;
		//int second_half_0_C = 0;
		//int first_half_1_C = 0;
		//int second_half_1_C = 0;
		//for (int j = 0; j < *puzzle->dim; j++) {
		//	if (puzzle->squares[i][j] == 0 && j < *puzzle->dim / 2) {
		//		first_half_0++;
		//	}
		//	if (puzzle->squares[i][j] == 1 && j < *puzzle->dim / 2) {
		//		first_half_1++;
		//	}
		//	if (puzzle->squares[i][j] == 0 && j >= *puzzle->dim / 2) {
		//		second_half_0++;
		//	}
		//	if (puzzle->squares[i][j] == 1 && j >= *puzzle->dim / 2) {
		//		second_half_1++;
		//	}
		//	if (puzzle->transponse[i][j] == 0 && j < *puzzle->dim / 2) {
		//		first_half_0_C++;
		//	}
		//	if (puzzle->transponse[i][j] == 1 && j < *puzzle->dim / 2) {
		//		first_half_1_C++;
		//	}
		//	if (puzzle->transponse[i][j] == 0 && j >= *puzzle->dim / 2) {
		//		second_half_0_C++;
		//	}
		//	if (puzzle->transponse[i][j] == 1 && j >= *puzzle->dim / 2) {
		//		second_half_1_C++;
		//	}
		//}
		////Check and change row
		//if (first_half_0 + first_half_1 == 0 && second_half_0 + second_half_1 == *puzzle->dim / 2) {
		//	printf("Lege eerste helft");
		//	//Check if max number of ones was reached. The +3-1 is needed to allow a ceiling function when dividing by three.
		//	if (*puzzle->dim/2 - second_half_1 == (*puzzle->dim / 2) - ((*puzzle->dim + 3 - 1) / 3)) {
		//		int empty_left = *puzzle->dim / 2 - 1;
		//		int empty_right = 0;
		//		for (int k = *puzzle->dim / 2 - 1; k >=0 ; k--) {
		//			if (empty_left / 3 > *puzzle->dim / 2 - second_half_1 || empty_right / 3 > *puzzle->dim / 2 - second_half_1) {
		//				add_number(puzzle, i, k, 0);
		//				changed = 0;
		//			}
		//			empty_left--;
		//			empty_right++;
		//		}
		//	}
		//	//Check if max number of zeros was reached. 
		//	if (*puzzle->dim / 2 - second_half_0 == (*puzzle->dim / 2) - ((*puzzle->dim + 3 - 1) / 3)) {
		//		int empty_left = *puzzle->dim / 2 - 1;
		//		int empty_right = 0;
		//		for (int k = *puzzle->dim / 2 - 1; k >= 0; k--) {
		//			if (empty_left / 3 > *puzzle->dim / 2 - second_half_0 || empty_right / 3 > *puzzle->dim / 2 - second_half_0) {
		//				add_number(puzzle, i, k, 1);
		//				changed = 0;
		//			}
		//			empty_left--;
		//			empty_right++;
		//		}
		//	}
		//}
		//if (first_half_0 + first_half_1 == *puzzle->dim / 2 && second_half_0 + second_half_1 == 0) {
		//	printf("lege 2e helft");
		//	//Check if max number of ones was reached. The +3-1 is needed to allow a ceiling function when dividing by three.
		//	if (*puzzle->dim / 2 - first_half_1 == (*puzzle->dim / 2) - ((*puzzle->dim + 3 - 1) / 3)) {
		//		printf("max1");
		//		int empty_left = 0;
		//		int empty_right = *puzzle->dim / 2 - 1;
		//		for (int k = *puzzle->dim / 2; k < *puzzle->dim; k++) {
		//			printf("resterend: %d\n", *puzzle->dim / 2 - first_half_1);
		//			if (empty_left / 3 > *puzzle->dim / 2 - first_half_1 || empty_right / 3 > *puzzle->dim / 2 - first_half_1) {
		//				printf("hier");
		//				add_number(puzzle, i, k, 0);
		//				changed = 0;
		//			}
		//			empty_left++;
		//			empty_right--;
		//		}
		//	}
		//	//Check if max number of zeros was reached. 
		//	if (*puzzle->dim / 2 - first_half_0 == (*puzzle->dim / 2) - ((*puzzle->dim + 3 - 1) / 3)) {
		//		printf("max0");
		//		int empty_left = 0;
		//		int empty_right = *puzzle->dim / 2 - 1;
		//		for (int k = *puzzle->dim / 2; k < *puzzle->dim; k++) {
		//			if (empty_left / 3 > *puzzle->dim / 2 - first_half_0 || empty_right / 3 > *puzzle->dim / 2 - first_half_0) {
		//				add_number(puzzle, i, k, 1);
		//				changed = 0;
		//			}
		//			empty_left++;
		//			empty_right--;
		//		}
		//	}
		//}
		////Check col
		////TO DO: UITWERKEN EN TESTGEVALLEN AANPASSEN.
	}
	return changed;
}

int eliminate_other_impossible_combos(BinaryPuzzle* puzzle) {

	return 0;
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