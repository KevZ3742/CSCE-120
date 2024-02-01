#include <iostream>
#include "functions.h"

using std::cout, std::endl;

bool is_valid_range(int a, int b) {
	if (a < 10 || b >= 10000 || a > b) {
        return false;
    }
	return true;
}

char classify_mv_range_type(int number) {
	// TODO(student): return 'M' if number has /\/\... pattern,
	// return 'V' if number has \/\/ pattern, and return 'N' otherwise
	return 'N';
}

void count_valid_mv_numbers(int a, int b) {
	// TODO(student): count the number of valid mountain ranges and valley
	// ranges in the range [a, b] and print out to console using the format
	// in Requirement 4 of the homework prompt
}