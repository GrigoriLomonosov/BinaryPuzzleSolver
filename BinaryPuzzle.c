#include "BinaryPuzzle.h"

//Checks whether the string only contains 1,0 or -.
int check_char_in_string(char* input) {
	if (input[0] == '\0') {
		return 0;
	}
	else {
		unsigned int i = 0;
		while (i<strlen(input)) {
			if (input[i] != '0' && input[i] != '1' && input[i] != '-') {
				return 0;
			}
			i++;
		}
		return 1;
	}
}

BinaryPuzzle* init_puzzle(char* input) {
	if (strlen(input)%2 != 0 || strlen(input) < pow(MIN_DIMENSION,2) || strlen(input) > pow(MAX_DIMENSION,2) || 
		check_char_in_string(input) != 1) {
		//printf("error: if n is the length of the inputstring, n should be even, >=36 and <= 1296\n");		
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
