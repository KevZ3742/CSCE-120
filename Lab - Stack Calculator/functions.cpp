#include "functions.h"
using std::cin, std::cout, std::endl, std::ostream, std::string;

#define INFO(X)  cout << "[INFO] ("<<__FUNCTION__<<":"<<__LINE__<<") " << #X << " = " << X << endl;
#define INFO_STRUCT(X) cout << "[INFO] ("<<__FUNCTION__<<":"<<__LINE__<<") " << #X << " count = " << X.count << endl;

void resize(Stack& stack, int new_capacity) {
    int* new_numbers = new int[new_capacity];
    for (int i = 0; i < stack.count; ++i) {
        new_numbers[i] = stack.numbers[i];
    }
    delete[] stack.numbers;
    stack.numbers = new_numbers;
    stack.capacity = new_capacity;
}

/**
 * ----- REQUIRED -----
 * Pushes number to top of stack. If stack is full, then resize stack's array.
 * @param   stack   Target stack.
 * @param   number  Number to push to stack.
 */
void push(Stack& stack, int number) {
    if (stack.count == stack.capacity) {
        int new_capacity = std::max(stack.capacity * 2, 1);
        resize(stack, new_capacity);
    }
    stack.numbers[stack.count++] = number;
}

/**
 * ----- REQUIRED -----
 * Pops number from top of stack. If stack is empty, return INT32_MAX.
 * @param   stack   Target stack.
 * @return          Value of popped number.
 */
int pop(Stack& stack) {
    if (stack.count == 0) {
        return INT32_MAX;
    }
    return stack.numbers[--stack.count];
}

/**
 * ----- REQUIRED -----
 * Returns the number at top of stack without popping it. If stack is empty, return INT32_MAX.
 * @param   stack   Target statck.
 * @return          Number at top of stack.
 */
int peek(const Stack& stack) {
    if (stack.count == 0) {
        return INT32_MAX;
    }
    return stack.numbers[stack.count - 1];
}
