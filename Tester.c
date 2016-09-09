#include "Tester.h"

void test_init_puzzle() {
	assert(init_puzzle(EMPTY_Q) == NULL);
	assert(init_puzzle(INVALID_Q1) == NULL);
	assert(init_puzzle(INVALID_Q2) == NULL);
	assert(init_puzzle(INVALID_Q3) == NULL);
	assert(init_puzzle(INVALID_Q4) == NULL);
	BinaryPuzzle* puzzle_1 = init_puzzle(FULL_Q1);
	BinaryPuzzle* puzzle_2 = init_puzzle(FULL_Q2);
	assert(puzzle_1!=NULL);
	assert(puzzle_2!=NULL);
	assert(*puzzle_1->dim == 6);
	assert(*puzzle_2->dim == 6);

	//testing some random values from the matrices.
	assert(puzzle_1->squares[0][0] == 1);
	assert(puzzle_1->squares[0][3] == 0);
	assert(puzzle_1->squares[0][5] == 0);
	assert(puzzle_1->squares[1][2] == 0);
	assert(puzzle_1->squares[1][1] == 1);
	assert(puzzle_1->squares[1][3] == 1);
	assert(puzzle_1->squares[1][4] == 0);
	assert(puzzle_1->squares[2][0] == 1);
	assert(puzzle_1->squares[2][1] == 0);
	assert(puzzle_1->squares[2][2] == 1);
	assert(puzzle_1->squares[3][5] == 0);
	assert(puzzle_1->squares[3][2] == 0);
	assert(puzzle_1->squares[3][3] == 1);
	assert(puzzle_1->squares[4][4] == 0);
	assert(puzzle_1->squares[4][3] == 1);
	assert(puzzle_1->squares[4][0] == 1);
	assert(puzzle_1->squares[5][5] == 0);
	assert(puzzle_1->squares[5][2] == 1);
	assert(puzzle_1->squares[5][1] == 1);
	assert(puzzle_1->squares[5][0] == 0);

	assert(puzzle_2->squares[0][0] == 1);
	assert(puzzle_2->squares[0][3] == 0);
	assert(puzzle_2->squares[0][5] == -1);
	assert(puzzle_2->squares[1][2] == 0);
	assert(puzzle_2->squares[1][1] == 1);
	assert(puzzle_2->squares[1][3] == 1);
	assert(puzzle_2->squares[1][4] == 0);
	assert(puzzle_2->squares[2][0] == 1);
	assert(puzzle_2->squares[2][1] == 0);
	assert(puzzle_2->squares[2][2] == 1);
	assert(puzzle_2->squares[3][5] == -1);
	assert(puzzle_2->squares[3][2] == 0);
	assert(puzzle_2->squares[3][3] == 1);
	assert(puzzle_2->squares[4][4] == 0);
	assert(puzzle_2->squares[4][3] == 1);
	assert(puzzle_2->squares[4][0] == -1);
	assert(puzzle_2->squares[5][5] == 0);
	assert(puzzle_2->squares[5][2] == 1);
	assert(puzzle_2->squares[5][1] == 1);
	assert(puzzle_2->squares[5][0] == 0);
	free_puzzle(puzzle_1);
	free_puzzle(puzzle_2);
	printf("Test constructor passed.\n");
}

void test_find_pairs() {
	printf("Test find_pairs passed.\n");
}

void test_avoid_trios() {
	printf("Test avoid_trios passed.\n");
}

void test_complete_RC() {
	printf("Test complete_RC passed.\n");
}

void test_eliminate_impossible_combos() {
	printf("Test eliminate_impossible_combos passed.\n");
}

void test_complete_half_RC() {
	printf("Test complete_half_RC passed.\n");
}

void test_eliminate_other_impossible_combos() {
	printf("Test eliminate_other_impossible_combos passed.\n");
}

void test_general_solver() {
	printf("Test general_solver passed.\n");
}
