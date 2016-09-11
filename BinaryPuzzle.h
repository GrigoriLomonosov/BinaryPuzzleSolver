#ifndef BINARYPUZZLE_H
#define BINARYPUZZLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <vector>
#include <stdbool.h>

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
} BinaryPuzzle;

/*
Only even dimensions between the boundaries are allowed. The input should only contain 0,1,-.
*/
BinaryPuzzle* init_puzzle(char* input);
void free_puzzle(BinaryPuzzle* puzzle);
void print_puzzle(BinaryPuzzle* puzzle);

/*
Returns True if there is atleast 1 empty cell.
*/
bool isEmpty(BinaryPuzzle* puzzle);


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
Finds pairs of 0's in the puzzle and fills the edges with 1's (analogue with pairs of 1).
Returns 0 if at least one pair is found and the edges were filled, 1 if not.
*/
int find_pairs(BinaryPuzzle* puzzle);

/*
Searches for 3 squares where the middle square is empty(-1) and the edge squares are both the same.
Returns 0 if at least one trio is found and the middle square is filled, 1 if not.
*/
int avoid_trios(BinaryPuzzle* puzzle);

/*
Each row/column should contain the same amount of 1's and 0's. Searches and fills a row/column
that can be filled based on this rule.
Returns 0 if at least one square in a row/column was filled, 1 if not.
*/
int complete_RC(BinaryPuzzle* puzzle);

/*
No two rows/columns can be identical. Searches and fills a row/column based on this rule.
Returns 0 if at least one square in a row/column was filled, 1 if not.
*/
int eliminate_impossible_combos(BinaryPuzzle* puzzle);

/*
When the first or last n/2 squares in a row are filled with n/2-floor((n/2)/3) 1's and n%3=1, then there is only one possibility
to fill in the remaining row. Analogue for column and 0's.
Returns 0 if at least one column or row was completed in this manner.
*/
int complete_half_RC(BinaryPuzzle* puzzle);

/*
Calculates all possible combos for a row/column based on what is already filled in, in that row/column.
Afterwards impossible combos are deleted based on the above rules. When the combos all have one (or more) square(s) in common, that square(s) is (are) filled.
Returns 0 if at least one square was filled, 1 if not.
*/
int eliminate_other_impossible_combos(BinaryPuzzle* puzzle);

/*
Solves a binary_puzzle
*/
void solve_puzzle(BinaryPuzzle* puzzle);

#endif