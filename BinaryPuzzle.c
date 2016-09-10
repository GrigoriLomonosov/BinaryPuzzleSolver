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
		for (int i = 0; i < dimension; i++) {
			puzzle_pointer->squares[i] = malloc(dimension*sizeof(int));
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
		return puzzle_pointer;
	}
}

void free_puzzle(BinaryPuzzle* puzzle) {
	for (int i = 0; i < 6; i++) {
		free(puzzle->squares[i]);
	}
	free(puzzle->squares);
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
					/*printf("puzzle1: \n");
					print_puzzle(puzzle_1);
					printf("puzzle2: \n");
					print_puzzle(puzzle_2);*/
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
		exit(1);
	}
	puzzle->squares[row][col] = number;
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
			if (puzzle->squares[j - 1][i] == -1 && 
				puzzle->squares[j][i] == puzzle->squares[j + 1][i] &&
				(puzzle->squares[j][i] == 0 || puzzle->squares[j][i] == 1) && 
				puzzle->squares[j + 2][i] == -1) {
					//0 becomes 1, 1 becomes 0
					add_number(puzzle, j - 1, i, (puzzle->squares[j][i] + 1) % 2);
					add_number(puzzle, j + 2, i, (puzzle->squares[j][i] + 1) % 2);
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
			if (puzzle->squares[j][i] == -1 &&
				puzzle->squares[j - 1][i] == puzzle->squares[j + 1][i] &&
				(puzzle->squares[j - 1][i] == 0 || puzzle->squares[j - 1][i] == 1)) {
				//0 becomes 1, 1 becomes 0
				add_number(puzzle, j, i, (puzzle->squares[j - 1][i] + 1) % 2);
				changed = 0;
			}
		}
	}
	return changed;
}

int complete_RC(BinaryPuzzle* puzzle) {

	return 0;
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

}