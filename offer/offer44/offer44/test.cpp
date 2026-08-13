#include <iostream>
using namespace std;

#if 0
int countOfIntegers(int digits);
int digitAtIndex(int index, int digits);
int beginNumber(int digits);

int digitAtIndex(int index)
{
	if (index <= 0)
		return 0;

	int digit = 1;
	while (1)
	{
		int number = countOfIntegers(digit);
		if (index < number * digit)
			return digitAtIndex(index, digit);
		index -= number * digit;
		++digit;
	}
	return -1;
}

// 计算digits区间有多少数字
int countOfIntegers(int digits)
{
	if (digits == 1)
		return 10;
	int ret = (int)std::pow(10, digits - 1);
	return ret * 9;
}
int digitAtIndex(int index, int digits)
{
	int number = beginNumber(digits) + index / digits;
	int numberRight = digits - index % digits;
	for (int i = 1; i < numberRight; ++i)
		number /= 10;
	return number % 10;
}
// 计算digits前有多少个数字
int beginNumber(int digits)
{
	if (digits == 1)
		return 0;
	return (int)std::pow(10, digits - 1);
}

#endif
int Count(int digit)
{
	if (digit == 1)
		return 10;
	int ret = (int)std::pow(10, digit - 1);
	return 9 * ret;
}


int beginCount(int digit)
{
	if (digit == 1)
		return 0;

	return (int)std::pow(10, digit - 1);
}


int findNthDigit(int index, int digit)
{
	int number = beginCount(digit) + index / digit;
	int numberRight = digit - index % digit;
	for (int i = 1; i < numberRight; ++i)
		number /= 10;
	return number % 10;
}



int digitAtIndex(int n) {
	if (n <= 0)
		return 0;
	int digit = 1;
	while (1)
	{
		int number = Count(digit);
		if ((unsigned int)n < (unsigned int)digit * number)
			return findNthDigit(n, digit);

		n -= digit * number;
		digit++;
	}
	return -1;
}

// ====================测试代码====================
void test(const char* testName, int inputIndex, int expectedOutput)
{
	if (digitAtIndex(inputIndex) == expectedOutput)
		cout << testName << " passed." << endl;
	else
		cout << testName << " FAILED." << endl;
}


int main()
{
	test("Test1", 0, 0);
	test("Test2", 10, 1);
	test("Test3", 9, 9);
	test("Test4", 10, 1);
	test("Test5", 189, 9);  // 数字99的最后一位，9
	test("Test6", 190, 1);  // 数字100的第一位，1
	test("Test7", 1000, 3); // 数字370的第一位，3
	test("Test8", 1001, 7); // 数字370的第二位，7
	test("Test9", 1002, 0); // 数字370的第三位，0
	return 0;
}