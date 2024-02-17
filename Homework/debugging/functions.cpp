#include <stdexcept>

int Largest(int a, int b, int c)
{
	int d = -2147483647;
	if (a > d)
		d = a;
	if (b > d)
		d = b;
	if (c > d)
		d = c;
	return d;
}

bool SumIsEven(int a, int b)
{
	return (a + b) % 2 == 0;
}

int BoxesNeeded(int apples)
{
	if (apples < 1)
		return 0;
	else
		return (apples + 19) / 20;
}

bool SmarterSection(int A_correct, int A_total, int B_correct, int B_total)
{
	if (A_correct < 0 || A_total < 0 || B_correct < 0 || B_total < 0 || A_correct > A_total || B_correct > B_total)
		throw std::invalid_argument("Invalid parameters");
	double val1 = static_cast<double>(A_correct) / A_total;
	double val2 = static_cast<double>(B_correct) / B_total;
	return val1 > val2;
}

bool GoodDinner(int pizzas, bool is_weekend) {
    return (pizzas > 9 && pizzas < 21 && !is_weekend) || (pizzas > 9 && is_weekend);
}

int SumBetween(int low, int high) {
    if (low > high)
        throw std::invalid_argument("Invalid parameters");
    long long val = static_cast<long long>(high - low + 1) * (low + high) / 2;
    if (val > 2147483647 || val < -2147483648)
        throw std::overflow_error("Invalid parameters");
    return static_cast<int>(val);
}

int Product(int a, int b)
{
	long long val = static_cast<long long>(a) * b;
	if (val > 2147483647 || val < -2147483648)
		throw std::overflow_error("Invalid parameters");
	return static_cast<int>(val);
}