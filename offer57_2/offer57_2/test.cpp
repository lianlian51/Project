#include <iostream>

void PrintContinuousSequence(int small, int big);

void FindContinuousSequence(int sum)
{
	if (sum < 3)
		return;

	int small = 1;
	int big = 2;
	int mid = (1 + sum) / 2;
	int curSum = small + big;
	while (small < mid)
	{
		if (curSum == sum)
			PrintContinuousSequence(small, big);

		while (curSum > sum)
		{
			curSum -= small;
			++small;

			if (curSum == sum)
				PrintContinuousSequence(small, big);
		}

		++big;
		curSum += big;
	}
}

void PrintContinuousSequence(int small, int big)
{
	for (int i = small; i <= big; ++i)
		printf("%d ", i);
	printf("\n");
}

// ====================²âÊÔ´úÂë====================
void Test(const char* testName, int sum)
{
	if (testName != nullptr)
		printf("%s for %d begins: \n", testName, sum);

	FindContinuousSequence(sum);
}

int main(int argc, char* argv[])
{
	Test("test1", 1);
	Test("test2", 3);
	Test("test3", 4);
	Test("test4", 9);
	Test("test5", 15);
	Test("test6", 100);

	return 0;
}