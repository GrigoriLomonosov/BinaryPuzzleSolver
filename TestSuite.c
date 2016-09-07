#include "Tester.h"

int main() {
	printf("Testing BinaryPuzzleSolver");
	test_init_puzzle("");
	test_find_pairs();
	test_avoid_trios();
	test_complete_RC();
	test_complete_half_RC();
	test_eliminate_impossible_combos();
	test_eliminate_other_impossible_combos();
	test_general_solver();
}
