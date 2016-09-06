#ifndef BINARYPUZZLE_H
#define BINARYPUZZLE_H

typedef struct BinaryPuzzle {
	int n;
	int** squares;
} BinaryPuzzle;

BinaryPuzzle* init_puzzle(char* input);
void free_puzzle(BinaryPuzzle* puzzle);

/*
Adds a 0 or 1 or '-1' to the given square in the puzzle.
 */
void add_number(int row, int col, int number);

/*
Finds pairs of 0's in the puzzle and fills the edges with 1's (analogue with pairs of 1).
Returns 1 if a pair is found and the edges were filled, 0 if not.
*/
int find_pair(BinaryPuzzle* puzzle);

/*
Searches for 3 squares where the middle square is empty(-1) and the edge squares are both the same.
Returns 1 if a trio is found and the middle square is filled, 0 if not.
*/
int avoid_trios(BinaryPuzzle* puzzle);

/*
Each row/column should contain the same amount of 1's and 0's. Searches and fills a row/column
that can be filled based on this rule.
Returns 1 if a row/column was filled, 0 if not.
*/
int complete_RC(BinaryPuzzle* puzzle);

/*
No two rows/columns can be identical. Searches and fills a row/column based on this rule.
Returns 1 if a row/column was filled, 0 if not.
*/
int eliminate_impossible_combos(BinaryPuzzle* puzzle);

/*
Searches for impossible combos based on a combination of the above rules.
Returns 1 if a square was filled, 0 if not.
*/
int eliminate_other_impossible_combos(BinaryPuzzle* puzzle);

#endif