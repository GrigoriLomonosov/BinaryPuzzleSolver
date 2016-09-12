//Code to check for memory leaks
#ifdef _MSC_VER
#include <crtdbg.h>
#endif

#include "Tester.h"

void test() {
	test_init_puzzle();
	test_find_pairs();
	test_avoid_trios();
	test_complete_RC();
	//test_eliminate_impossible_combos();
	//test_complete_half_RC();
	//test_eliminate_other_impossible_combos();
	//test_general_solver();
}

void run() {
}

int main() {
	printf("Testing BinaryPuzzleSolver\n\n");
	#ifdef _DEBUG
	test();
	#else
	run();
	#endif
	getchar();
	#ifdef _MSC_VER
		_CrtDumpMemoryLeaks();
	#endif
}
