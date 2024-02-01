#include <iostream>
#include "functions.h"

using std::cout, std::endl;

int reverseInteger(int num) {
    int reversed = 0;

    while (num != 0) {
        int digit = num % 10;
        reversed = reversed * 10 + digit;
        num /= 10;
    }

    return reversed;
}

bool isLandform(int num, bool isGreater){
	// isGreater decides the direction of the sign. True(<), False(>)
	int reversedNum = reverseInteger(num);
	int initialDigit = reversedNum % 10;
	reversedNum = reversedNum / 10;

	while (reversedNum != 0)
	{
		int currentDigit = reversedNum % 10;
		reversedNum = reversedNum / 10;

		if(isGreater){
			if (currentDigit < initialDigit){
				initialDigit = currentDigit;
			}else{
				return false;
			}
			isGreater = false;
		}else{
			if (currentDigit > initialDigit){
				initialDigit = currentDigit;
			}else{
				return false;
			}
			isGreater = true;
		}
	}

	return true;
}

bool is_valid_range(int a, int b) {
	if (a < 10 || b >= 10000 || a > b) {
        return false;
    }else{
		return true;
	}
}

char classify_mv_range_type(int number) {
	// TODO(student): return 'M' if number has /\/\... pattern,
	// return 'V' if number has \/\/ pattern, and return 'N' otherwise

	if (number / 10 == 0)
	{
		return 'N';
	}

	// Check for ending in 0 edge case
	if (number % 10 == 0)
	{
		number = number * 10 + (reverseInteger(number) % 10);
	}

	// isGreater = false and returns true, then it is a mountain
	if (isLandform(number, false))
	{
		return 'M';
	}
	// isGreater = true and returns true, then it is a valley
	else if (isLandform(number, true))
	{
		return 'V';
	}
	// Otherwise, it is neither
	else{
		return 'N';
	}
}

void count_valid_mv_numbers(int a, int b) {
	// TODO(student): count the number of valid mountain ranges and valley
	// ranges in the range [a, b] and print out to console using the format
	// in Requirement 4 of the homework prompt
	int numMountains = 0;
	int numValleys = 0;

	for (int i = a; i <= b; i++)
	{
		char type = classify_mv_range_type(i);
		if (type == 'M')
		{
			numMountains++;
		}else if (type == 'V')
		{
			numValleys++;
		}
	}

	cout << "There are " << numMountains << " mountain ranges and " << numValleys << " valley ranges between " << a << " and " << b << "." << endl;
}

