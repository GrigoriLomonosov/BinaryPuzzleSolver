#ifndef TESTER_H
#define TESTER_H

//Define this macro to ignore all assertions
//#define NDEBUG

#include "BinaryPuzzle.h"
#include <assert.h>

#define SENTINEL "sentinel"

#define EMPTY_Q ""
#define FULL_Q1 "101010010101101001010110100101011010"
#define FULL_Q2 "1-101--1010110100101011---0101011010"
//invalid char, only 1,0,- allowed in input string
#define INVALID_Q1 "101010010101011010010101101001a1011010"
//invalid dimensions, 35 char
#define INVALID_Q2 "1010100101010110100101011010011011010"
//invalid dimensions, 37 char
#define INVALID_Q3 "101010010101011010010101101001010110101"
//invalid dimensions, to small (4x4)
#define INVALID_Q4 "0101101010010110"

//Testcases for find_pairs
#define Q1 "--------00--------------------------",\
"--------11--------------------------",\
"----------0-----0-------------------",\
"----------1-----1-------------------",\
"--------00----------00--------------",\
"--------11----------11--------------",\
"-------0-----0-------0-----0--------",\
"-------1-----1-------1-----1--------",\
"--00-------------------0-----0------",\
"--11-------------------1-----1------",\
"--00-------------------1-----1------",\
"--11-------------------0-----0------",\
"-------0-----0-------1-----1--------",\
"--------00----------11--------------",\
"00----------------------------------",\
"11----------------------------------",\
"----00------------------------------",\
"----11------------------------------",\
"0-----0-----------------------------",\
"-----1-----1------------------------",\
"------------------------0-----0-----",\
"-----------------------------1-----1"
#define A1 "-------1001-------------------------",\
"-------0110-------------------------",\
"----1-----0-----0-----1-------------",\
"----0-----1-----1-----0-------------",\
"-------1001--------1001-------------",\
"-------0110--------0110-------------",\
"-1-----0-----0-1---1-0-----0-----1--",\
"-0-----1-----1-0---0-1-----1-----0--",\
"-1001------------1-----0-----0-----1",\
"-0110------------0-----1-----1-----0",\
"-1001------------0-----1-----1-----0",\
"-0110------------1-----0-----0-----1",\
"-1-----0-----0-0---1-1-----1-----0--",\
"-------1001--------0110-------------",\
"001---------------------------------",\
"110---------------------------------",\
"---100------------------------------",\
"---011------------------------------",\
"0-----0-----1-----------------------",\
"-----1-----1-----0------------------",\
"------------------1-----0-----0-----",\
"-----------------------0-----1-----1"

//Testcases for avoid_trios
#define Q2 "-------1-1--------------------------",\
"----------------------1-----------1-",\
"-------1-1--------------1-1---------",\
"-----1-----------1----1-----------1-",\
"-------1-1------------1-----------1-",\
"-------0-0--------------------------",\
"----------------------0-----------0-",\
"-------0-0--------------0-0---------",\
"-----0-----------0----0-----------0-",\
"-------0-0------------0-----------0-",\
"-------1-1--------------0-0---------",\
"-----1-----------1----0-----------0-",\
"-------0-0------------1-----------1-",\
"-----1-----------1------0-0---------"
#define A2 "-------101--------------------------",\
"----------------------1-----0-----1-",\
"-------101--------------101---------",\
"-----1-----0-----1----1-----0-----1-",\
"-------101------------1-----0-----1-",\
"-------010--------------------------",\
"----------------------0-----1-----0-",\
"-------010--------------010---------",\
"-----0-----1-----0----0-----1-----0-",\
"-------010------------0-----1-----0-",\
"-------101--------------010---------",\
"-----1-----0-----1----0-----1-----0-",\
"-------010------------1-----0-----1-",\
"-----1-----0-----1------010---------"

//Testcases for complete_RC
#define Q3 "------10100-------------------------",\
"------01011-------------------------",\
"-----0-----1-----0-----1-----1------",\
"-----1-----0-----1-----0-----0------",\
"--1-----0-----1-----------------1---",\
"--0-----1-----0-----------------0---",\
"------101--1------------------------",\
"------------------010--0------------",\
"------10100-------01011-------------",\
"101--1------------010--0------------",\
"0----11----00----11----01----0------",\
"--10----01----10----------------10--",\
"10100----1-----0-----1-----1--------",\
"10100-0-----1-----------------1-----",\
"101--10-----1-----------------1-----",\
"101--1--0-----1-----0-----0---------"
#define A3 "------101001------------------------",\
"------010110------------------------",\
"-----0-----1-----0-----1-----1-----0",\
"-----1-----0-----1-----0-----0-----1",\
"--1-----0-----1-----0-----0-----1---",\
"--0-----1-----0-----1-----1-----0---",\
"------101001------------------------",\
"------------------010110------------",\
"------101001------010110------------",\
"101001------------010110------------",\
"0----11----00----11----01----00----1",\
"--10----01----10----01----01----10--",\
"101001---1-----0-----1-----1-----0--",\
"1010010-----1-----0-----0-----1-----",\
"1010010-----1-----0-----0-----1-----",\
"101001--0-----1-----0-----0-----1---"

//Testcases for eliminate_impossible_combos
#define Q4 "------011010------------------0110--",\
"-0---0-1---1-1---1-0---0-1-----0----"
#define A4 "------011010------------------011001",\
"-0---0-1---1-1---1-0---0-1---0-0---1"

//Testcases for complete_pattern_RC
#define Q5 "------------------110---------------",\
"------------------001---------------",\
"---------------------011------------",\
"---------------------100------------",\
"---------------------101------------",\
"---------------------010------------",\
"---------------------110------------",\
"---------------------001------------",\
"------------------101---------------",\
"------------------010---------------",\
"------------------011---------------",\
"------------------100---------------",\
"1---01------------------------------",\
"0---10------------------------------",\
"10---1------------------------------",\
"01---0------------------------------",\
"1-----1-----0-----------------------", \
"0-----0-----1-----------------------", \
"------------------0-----1-----1-----", \
"------------------1-----0-----0-----", \
"------------------1-----0-----1-----", \
"------------------0-----1-----0-----", \
"------------------1-----1-----0-----", \
"------------------0-----0-----1-----", \
"1-----0-----1-----------------------", \
"0-----1-----0-----------------------", \
"0-----1-----1-----------------------", \
"1-----0-----0-----------------------", \
"1-----------------------0-----1-----", \
"0-----------------------1-----0-----", \
"1-----0-----------------------1-----", \
"0-----1-----------------------0-----", \
"------------------------0---10------",\
"------------------00--00------------",\
"----------------110---10----------------------------------------",\
"----------------011---10----------------------------------------",\
"----------------101---10----------------------------------------",\
"----------------110---01----------------------------------------",\
"----------------011---01----------------------------------------",\
"----------------101---01----------------------------------------",\
"----------------01---011----------------------------------------",\
"----------------01---110----------------------------------------",\
"----------------01---101----------------------------------------",\
"----------------10---011----------------------------------------",\
"----------------10---110----------------------------------------",\
"----------------10---101----------------------------------------",\
"----------------1----101----------------------------------------",\
"----------------11----10----------------------------------------",\
"----------------11----01----------------------------------------",\
"----------------101----1----------------------------------------",\
"----------------01----11----------------------------------------",\
"----------------10----11----------------------------------------",\
"----------------11-----1----------------------------------------",\
"----------------1-----11----------------------------------------",\
"----------------1-----10----------------------------------------",\
"----------------0-----11----------------------------------------",\
"----------------1-----01----------------------------------------",\
"----------------01-----1----------------------------------------",\
"----------------11-----0----------------------------------------",\
"----------------10-----1----------------------------------------",\
"----------------1------1----------------------------------------",\
"----------------001---01----------------------------------------",\
"----------------100---01----------------------------------------",\
"----------------010---01----------------------------------------",\
"----------------001---10----------------------------------------",\
"----------------100---10----------------------------------------",\
"----------------010---10----------------------------------------",\
"----------------10---010----------------------------------------",\
"----------------10---101----------------------------------------",\
"----------------10---110----------------------------------------",\
"----------------01---100----------------------------------------",\
"----------------01---101----------------------------------------",\
"----------------01---110----------------------------------------",\
"----------------0----110----------------------------------------",\
"----------------00----01----------------------------------------",\
"----------------00----10----------------------------------------",\
"----------------010----0----------------------------------------",\
"----------------10----00----------------------------------------",\
"----------------01----00----------------------------------------",\
"----------------00-----0----------------------------------------",\
"----------------0-----00----------------------------------------",\
"----------------0-----01----------------------------------------",\
"----------------1-----00----------------------------------------",\
"----------------0-----10----------------------------------------",\
"----------------10-----0----------------------------------------",\
"----------------00-----1----------------------------------------",\
"----------------01-----0----------------------------------------",\
"----------------0------0----------------------------------------",\
"--------------------------------------------------11011---------------------------------------------"
#define A5 "------------------110--0------------",\
"------------------001--1------------",\
"------------------0--011------------",\
"------------------1--100------------",\
"---------------------101------------",\
"---------------------010------------",\
"---------------------110------------",\
"---------------------001------------",\
"------------------101---------------",\
"------------------010---------------",\
"------------------011---------------",\
"------------------100---------------",\
"10--01------------------------------",\
"01--10------------------------------",\
"10--01------------------------------",\
"01--10------------------------------",\
"1-----1-----0-----------------0-----", \
"0-----0-----1-----------------1-----", \
"0-----------------0-----1-----1-----", \
"1-----------------1-----0-----0-----", \
"------------------1-----0-----1-----", \
"------------------0-----1-----0-----", \
"------------------1-----1-----0-----", \
"------------------0-----0-----1-----", \
"1-----0-----1-----------------------", \
"0-----1-----0-----------------------", \
"0-----1-----1-----------------------", \
"1-----0-----0-----------------------", \
"1-----0-----------------0-----1-----", \
"0-----1-----------------1-----0-----", \
"1-----0-----------------0-----1-----", \
"0-----1-----------------1-----0-----", \
"------------------------01--10------",\
"------------------00--00------------",\
"----------------110--010----------------------------------------",\
"----------------011---10----------------------------------------",\
"----------------101---10----------------------------------------",\
"----------------11001001----------------------------------------",\
"----------------0110--01----------------------------------------",\
"----------------1010--01----------------------------------------",\
"----------------010--011----------------------------------------",\
"----------------01---110----------------------------------------",\
"----------------01---101----------------------------------------",\
"----------------10010011----------------------------------------",\
"----------------10--0110----------------------------------------",\
"----------------10--0101----------------------------------------",\
"----------------10--0101----------------------------------------",\
"----------------110--010----------------------------------------",\
"----------------1100-001----------------------------------------",\
"----------------1010--01----------------------------------------",\
"----------------010--011----------------------------------------",\
"----------------100-0011----------------------------------------",\
"----------------1100-001----------------------------------------",\
"----------------100-0011----------------------------------------",\
"----------------1-----10----------------------------------------",\
"----------------0-----11----------------------------------------",\
"----------------1-----01----------------------------------------",\
"----------------01-----1----------------------------------------",\
"----------------11-----0----------------------------------------",\
"----------------10-----1----------------------------------------",\
"----------------1------1----------------------------------------",\
"----------------001--101----------------------------------------",\
"----------------100---01----------------------------------------",\
"----------------010---01----------------------------------------",\
"----------------00110110----------------------------------------",\
"----------------1001--10----------------------------------------",\
"----------------0101--10----------------------------------------",\
"----------------10---010----------------------------------------",\
"----------------10--0101----------------------------------------",\
"----------------10--0110----------------------------------------",\
"----------------01101100----------------------------------------",\
"----------------01---101----------------------------------------",\
"----------------01---110----------------------------------------",\
"----------------0----110----------------------------------------",\
"----------------001--101----------------------------------------",\
"----------------0011-110----------------------------------------",\
"----------------0101--10----------------------------------------",\
"----------------101--100----------------------------------------",\
"----------------011-1100----------------------------------------",\
"----------------0011-110----------------------------------------",\
"----------------011-1100----------------------------------------",\
"----------------0-----01----------------------------------------",\
"----------------1-----00----------------------------------------",\
"----------------0-----10----------------------------------------",\
"----------------10-----0----------------------------------------",\
"----------------00-----1----------------------------------------",\
"----------------01-----0----------------------------------------",\
"----------------0------0----------------------------------------",\
"--------------------------------------------------1101100-00----------------------------------------"

//Testcases for eliminate_other_impossible_combos
#define Q6 "-0--0-110010001--10-----1-0------1--"
#define A6 "-0--0-110010001--10-----1-01-----1--"

//General binarypuzzles in different dimensions
#define Q7 "--1---00-1--0--------------1------0-",\
"---11--0-0---0---00-----1--------------1--1-----0---------------",\
"-1-1-0--1-0-0-------------11----1--0----0----------------00-1------1-1--0---0---------0-1-----0--0--",\
"--------0--0------0--00---0---1--------1------1---1-----1-----0--------1--1-0--1----------1-------01",\
"---01---0-1-1---1--1-------1---1--0-------1-----0----0-0-1-1-----0-1----------0-1------1---0----0--0",\
"-------0-0-11--0----0-1--0-01-------1-----0--1--------------0-------0------------1-----0---1----1---",\
"-----0--1-----0--0--11--------1--00---0----0---1---1---0--------00--1-------1-------------------1-1-",\
"----10-------11----0---1-1-1--1---1-------0----11----0-10-0-----1----1-0------0-------1------1--1---1-0--1--0--------1-1----1-0-10-1----0-----1-------00-----0-----------1-------0------0---0----0--"
#define A7 "101010001101010011110010101100010101",\
"0101101000101011100101011100101001100101101100100100110110110100",\
"0101100110010101001110101011001011001001010011011001100110011001001101100110011001101100101010011001",\
"0110110100001101100110011001101100100101011001101010110010100101100101010011001110100110101001001101",\
"0110101001101001100110011001100101011010011001100110101001010101100110010101100110101001101001010110",\
"1001011010011010010101101010101001011001100101010101101001100011011001100110011001100100111100101100",\
"1001100110001001101111011001001010011001011001011001011001011011001010011001100101001101011001101010",\
"0101101010100110011001010101101001101010100110011001100101011001100101100110110010100110010011011000110011010101110011010010100010110011010110110010110010110010010011010110011010011010010101011010"


void test_init_puzzle();

void test_find_pairs();
void test_avoid_trios();
void test_complete_RC();
void test_eliminate_impossible_combos();
void test_complete_half_RC();
void test_eliminate_other_impossible_combos();

void test_general_solver();


#endif // !TESTER_H

