#ifndef BINARYPUZZLE_H
#define BINARYPUZZLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

#include "RowPossibilities.h"

#define MIN_DIMENSION 6
#define MAX_DIMENSION 36

/*
The field transponse is the transponse of the squares matrix. The transponse is kept because the matrix will be traversed several times
in column-major order. This helps us prevent cache-missers, especially with big matrices.
*/
typedef struct BinaryPuzzle {
	int* dim;
	int** squares;
	int** transponse;
	RowPossibilities** row_possibilities;
	RowPossibilities** col_possibilities
} BinaryPuzzle;

/*
Only even dimensions between the boundaries are allowed. The input should only contain 0,1,-.
*/
BinaryPuzzle* init_puzzle(int);
BinaryPuzzle* init_puzzle_by_pattern(char* input);
void free_puzzle(BinaryPuzzle* puzzle);
void print_puzzle(BinaryPuzzle* puzzle);

/*
Returns True if there is atleast 1 empty cell.
*/
bool hasEmptyCell(BinaryPuzzle* puzzle);


/*
Deep Copy, Duh.
*/
BinaryPuzzle* clone(BinaryPuzzle* puzzle);

/*
Adds a 0 or 1 or '-1' to the given square in the puzzle.
*/
void add_number(BinaryPuzzle* puzzle, int row, int col, int number);

/*
Compares two binary_puzzles.
Returns 0 if and only if the 2 binary_puzzles have the same dimension and every square is identical to the square of the other
binary_puzzle with the same coordinates.
*/
int compare_puzzles(BinaryPuzzle* puzzle_1, BinaryPuzzle* puzzle_2);

/*
Returns 0 if and only if a given puzzle is a valid solution.
*/
int is_valid_solution(BinaryPuzzle* puzzle);

/*
Finds pairs of 0's in the puzzle and fills the edges with 1's (analogue with pairs of 1).
Returns true if at least one pair is found and the edges were filled, false if not.
*/
bool find_pairs(BinaryPuzzle* puzzle);

/*
Searches for 3 squares where the middle square is empty(-1) and the edge squares are both the same.
Returns true if at least one trio is found and the middle square is filled, false if not.
*/
bool avoid_trios(BinaryPuzzle* puzzle);

/*
Each row/column should contain the same amount of 1's and 0's. Searches and fills a row/column
that can be filled based on this rule.
Returns true if at least one square in a row/column was filled, false if not.
*/
bool complete_RC(BinaryPuzzle* puzzle);

/*
Checks every square if a 1 or 0 can be filled in based on the 3 rules of a binary puzzle. 
Returns true if at least one square in was filled, false if not.
*/
bool eliminate_impossible_combos(BinaryPuzzle* puzzle);

/*
Searches longest pattern of consecutive empty squares in a row and counts the remaining available 1's.
We can not fill in a 1 in the squares that divide the pattern in 2 parts of which floor(k) is greater 
then the remaining number of 1's, with k=length(part)/3. 
Also, when the pattern is preceded (or followed) by a 0, then there should be at least one 1 in the first (or last)
2 squares. We then check if there are squares that divide the pattern minus the first 2 squares (and/or the last 2 squares)
in 2 parts of which floor(k) is greater then the remaining number of 1's -1 (or -2), with k=length(part)/3. If so a 1 cannot
be filled in. All these squares are then filled with a 0.
The situation where the pattern is preceded (or followed) by two consecutive zeros, should not be possible as this function
will always be called after find_pairs. No special measures were taken, to take this situation into account.
Analogue for columns and zeros.
Returns true if and only a square was filled.
*/
bool complete_pattern_RC(BinaryPuzzle* puzzle);

/*
Calculates all possible combos for a row/column based on what is already filled in, in that row/column.
Afterwards impossible combos are deleted based on the above rules. When the combos all have one (or more) square(s) in common, that square(s) is (are) filled.
Returns true if at least one square was filled, false if not.
*/
bool eliminate_other_impossible_combos(BinaryPuzzle* puzzle);

/*
Solves a binary_puzzle
*/
void solve_puzzle(BinaryPuzzle** puzzle);

#endif