#ifndef PASSING_BY_REFERENCE
#define PASSING_BY_REFERENCE

struct example {
	int value = 2;
};

void function_one(/* TODO: fill with the appropriate arguments */ int i, int& j);
void function_two(/* TODO: fill with the appropriate arguments */ example& ex);
void function_three(int* k, int& l);
void function_four(/* TODO: fill with the appropriate arguments */ int arr[], int size, int& lowest, int& highest);

#endif