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

BinaryPuzzle* init_puzzle(char* input) {
	if (strlen(input)%2 != 0 || strlen(input) < pow(MIN_DIMENSION,2) || strlen(input) > pow(MAX_DIMENSION,2) || 
		check_char_in_string(input) != 0) {
		//printf("error: if n is the length of the inputstring, n should be even, >=36 and <= 1296, and only contain '0','1' or '-'\n");		
		return NULL;
		//exit(1);
	}
	else
	{
		BinaryPuzzle* puzzle_pointer = malloc(sizeof(BinaryPuzzle));
		if (!puzzle_pointer) {
			printf("ERROR: Allocation failed, insufficient memory for BinaryPuzzle?\n");
			exit(1);
		}
		int dimension = (int) sqrt(strlen(input));
		puzzle_pointer->dim = malloc(sizeof(int));
		*(puzzle_pointer->dim) = dimension;
		puzzle_pointer->squares = malloc(dimension*sizeof(int*));
		puzzle_pointer->transponse = malloc(dimension*sizeof(int*));
		for (int i = 0; i < dimension; i++) {
			puzzle_pointer->squares[i] = malloc(dimension*sizeof(int));
			puzzle_pointer->transponse[i] = malloc(dimension*sizeof(int));
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
	for (int i = 0; i < puzzle->dim; i++) {
		if(puzzle->squares[i])
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
			printf("%d", puzzle->squares[i][j]);
		}
		printf("\n");
	}
	printf("\n");
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

void add_number(BinaryPuzzle* puzzle, int row, int col, int number) {
	if (row < 0 || row > *puzzle->dim || col < 0 || col > *puzzle->dim) {
		printf("ERROR: The given coordinates fall out of scope of the matrix dimensions.");
		//exit(1);
	}
	//printf("row: %d col: %d nr: %d", row, col, number);
	puzzle->squares[row][col] = number;
	puzzle->transponse[col][row] = number;
}

int find_pairs(BinaryPuzzle* puzzle) {
	int changed = 1;
	for (int i = 0; i < *puzzle->dim; i++) {
		for (int j = 1; j < *puzzle->dim-2; j++) {
			//Check row
			if (puzzle->squares[i][j - 1] == -1 && 
				puzzle->squares[i][j] == puzzle->squares[i][j + 1] && 
				(puzzle->squares[i][j] == 0 || puzzle->squares[i][j] == 1) && 
				puzzle->squares[i][j + 2] == -1) {
					//0 becomes 1, 1 becomes 0
					add_number(puzzle, i, j - 1, (puzzle->squares[i][j] + 1) % 2);
					add_number(puzzle, i, j + 2, (puzzle->squares[i][j] + 1) % 2);
					changed = 0;
			}
			//Check col
			if (puzzle->transponse[i][j - 1] == -1 &&
				puzzle->transponse[i][j] == puzzle->transponse[i][j + 1] &&
				(puzzle->transponse[i][j] == 0 || puzzle->transponse[i][j] == 1) &&
				puzzle->transponse[i][j + 2] == -1) {
				//0 becomes 1, 1 becomes 0
				add_number(puzzle, j - 1, i, (puzzle->transponse[i][j] + 1) % 2);
				add_number(puzzle, j + 2, i, (puzzle->transponse[i][j] + 1) % 2);
				changed = 0;
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
			else {
				add_number(puzzle, i, coordinates[0], 1);
			}
			changed = 0;
		}
		if (count_1 == *puzzle->dim / 2) {
			if (count_empty == 2) {
				add_number(puzzle, i, coordinates[0], 0);
				add_number(puzzle, i, coordinates[1], 0);
			}
			else {
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
				add_number(puzzle, coordinates_C[0],i , 1);
				add_number(puzzle, coordinates_C[1],i , 1);
			}
			else {
				add_number(puzzle, coordinates_C[0],i , 1);
			}
			changed = 0;
		}
		if (count_1_C == *puzzle->dim / 2) {
			if (count_empty_C == 2) {
				add_number(puzzle, coordinates_C[0],i , 0);
				add_number(puzzle, coordinates_C[1],i , 0);
			}
			else {
				add_number(puzzle, coordinates_C[0],i , 0);
			}
			changed = 0;
		}
	}
	return changed;
}

int eliminate_impossible_combos(BinaryPuzzle* puzzle) {

	return 0;
}

int complete_half_RC(BinaryPuzzle* puzzle) {

	return 0;
}

int eliminate_other_impossible_combos(BinaryPuzzle* puzzle) {

	return 0;
}

void solve_puzzle(BinaryPuzzle* puzzle) {
	//Werken met een kopie om onverwachte, externe veranderingen te vermijden.
}