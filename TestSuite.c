//Code to check for memory leaks
#ifdef _MSC_VER
#include <crtdbg.h>
#endif

#include "Tester.h"

int main() {
	printf("Testing BinaryPuzzleSolver\n\n");
	test_init_puzzle();
	test_find_pairs();
	test_avoid_trios();
	//test_complete_RC();
	//test_complete_half_RC();
	//test_eliminate_impossible_combos();
	//test_eliminate_other_impossible_combos();
	//test_general_solver();
	getchar();
	#ifdef _MSC_VER
		_CrtDumpMemoryLeaks();
	#endif
}
