#include <iostream>
#include <vector>

int InversePairsCore(int* data, int* copy, int start, int end);

int InversePairs(int* data, int length)
{
	if (data == nullptr || length <= 0)
		return 0;

	int* copy = new int[length];
	for (int i = 0; i < length; ++i)
		copy[i] = data[i];
	int count = InversePairsCore(data, copy, 0, length - 1);

	return count;
}

int InversePairsCore(int* data, int* copy, int start, int end)
{
	if (end == start)
	{
		copy[start] = data[start];
		return 0;
	}

	int length = (end - start) / 2;
	int left = InversePairsCore(copy, data, start, start + length);
	int right = InversePairsCore(copy, data, start + length + 1, end);

	int i = start + length; // i是前半段的最后一个数字的下标
	int j = end;
	int copyIndex = end;
	int count = 0;
	while (i >= start && j >= start + length + 1)
	{
		if (data[i] > data[j])
		{
			copy[copyIndex--] = data[i--];
			count += j - start - length;
		}
		else
		{
			copy[copyIndex--] = data[j--];
		}
	}

	for (; i >= start; --i)
		copy[copyIndex--] = data[i];
	for (; j >= start + length + 1; --j)
		copy[copyIndex--] = data[j];

	return left + right + count;
#if 0
	if (start >= end)
	{
		copy[start] = data[start];
		return 0;
	}
	int length = (end - start) / 2;
	int left = InversePairsCore(data, copy, start, start + length);
	int right = InversePairsCore(data, copy, start + length + 1, end);

	int i = start + length;
	int j = end;
	int copyIndex = end;
	int count = 0;
	while (i >= start && j >= start + length + 1)
	{
		if (data[i] > data[j])
		{
			copy[copyIndex--] = data[i--];
			count += j - length - start;
		}
		else
			copy[copyIndex--] = data[j--];
	}
	for (; i >= start; --i)
		copy[copyIndex--] = data[i];

	for (; j >= start + length + 1; --j)
		copy[copyIndex--] = data[j];

	return left + right + count;
#endif
}



// ====================测试代码====================
void Test(char* testName, int* data, int length, int expected)
{
	if (testName != nullptr)
		printf("%s begins: ", testName);

	if (InversePairs(data, length) == expected)
		printf("Passed.\n");
	else
		printf("Failed.\n");
}

void Test1()
{
	int data[] = { 1, 2, 3, 4, 7, 6, 5 };
	int expected = 3;

	Test("Test1", data, sizeof(data) / sizeof(int), expected);
}

// 递减排序数组
void Test2()
{
	int data[] = { 6, 5, 4, 3, 2, 1 };
	int expected = 15;

	Test("Test2", data, sizeof(data) / sizeof(int), expected);
}

// 递增排序数组
void Test3()
{
	int data[] = { 1, 3, 2, 3, 1};
	int expected = 4;

	Test("Test3", data, sizeof(data) / sizeof(int), expected);
}

// 数组中只有一个数字
void Test4()
{
	int data[] = { 1 };
	int expected = 0;

	Test("Test4", data, sizeof(data) / sizeof(int), expected);
}


// 数组中只有两个数字，递增排序
void Test5()
{
	int data[] = { 1, 2 };
	int expected = 0;

	Test("Test5", data, sizeof(data) / sizeof(int), expected);
}

// 数组中只有两个数字，递减排序
void Test6()
{
	int data[] = { 7, 5, 6, 4 };
	int expected = 5;

	Test("Test6", data, sizeof(data) / sizeof(int), expected);
}

// 数组中有相等的数字
void Test7()
{
	int data[] = { 1, 2, 1, 2, 1 };
	int expected = 3;

	Test("Test7", data, sizeof(data) / sizeof(int), expected);
}

void Test8()
{
	int expected = 0;

	Test("Test8", nullptr, 0, expected);
}

int main(int argc, char* argv[])
{
	Test1();
	Test2();
	Test3();
	Test4();
	Test5();
	Test6();
	Test7();
	Test8();

	return 0;
}