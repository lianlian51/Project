#include <iostream>

unsigned int FindFirstBitIs1(int num);
bool IsBit1(int num, unsigned int indexBit);

void FindNumsAppearOnce(int data[], int length, int* num1, int* num2)
{
	if (data == nullptr || length <= 0)
		return;

	int result = 0;
	for (int i = 0; i < length; ++i)
	{
		result ^= data[i];
	}

	int indexOf1 = FindFirstBitIs1(result);

	*num1 = *num2 = 0;
	for (int i = 0; i < length; ++i)
	{
		if (IsBit1(data[i], indexOf1))
			*num1 ^= data[i];
		else
			*num2 ^= data[i];
	}
}

// 判断第几位是1
unsigned int FindFirstBitIs1(int num)
{
	unsigned int index = 0;
	while ((num & 1) == 0 && index < 8 * sizeof(int))
	{
		num >>= 1;
		++index;
	}
	return index;
}

// 这个数字的第几位是不是1
bool IsBit1(int num, unsigned int indexBit)
{
	num >>= indexBit;
	return (num & 1);
}


// ====================测试代码====================
void Test(const char* testName, int data[], int length, int expected1, int expected2)
{
	if (testName != nullptr)
		printf("%s begins: ", testName);

	int result1, result2;
	FindNumsAppearOnce(data, length, &result1, &result2);

	if ((expected1 == result1 && expected2 == result2) ||
		(expected2 == result1 && expected1 == result2))
		printf("Passed.\n\n");
	else
		printf("Failed.\n\n");
}

void Test1()
{
	int data[] = { 2, 4, 3, 6, 3, 2, 5, 5 };
	Test("Test1", data, sizeof(data) / sizeof(int), 4, 6);
}

void Test2()
{
	int data[] = { 4, 6 };
	Test("Test2", data, sizeof(data) / sizeof(int), 4, 6);
}

void Test3()
{
	int data[] = { 4, 6, 1, 1, 1, 1 };
	Test("Test3", data, sizeof(data) / sizeof(int), 4, 6);
}

int main(int argc, char* argv[])
{
	Test1();
	Test2();
	Test3();

	return 0;
}