#include <cstring>
#include <cstdio>
#include <cstdlib>


int PowerBase10(unsigned int n)
{
	int ret = 1;
	for (unsigned int i = 0; i < n; ++i)
		ret *= 10;
	return ret;
}


int NumberOf1(const char* strN)
{
	// 1.特殊情况判断
	if (!strN || *strN < '0' || *strN > '9' || *strN == '\0')
		return 0;

	// 2.递归退出条件
	unsigned int length = static_cast<unsigned int>(strlen(strN));
	int first = *strN - '0';
	if (length == 1 && first == 0)
		return 0;
	if (length == 1 && first > 0)
		return 1;

	// 3.计算最高位的次数
	int numDigit = 0;
	if (first > 1)
		numDigit = PowerBase10(length - 1);
	else if (first == 1)
		numDigit = atoi(strN + 1) + 1;

	// 4.计算剩余位的次数
	int otherDigit = first * (length - 1) * PowerBase10(length - 2);

	// 5.计算当前位的次数
	int curDigit = NumberOf1(strN + 1);

	return numDigit + otherDigit + curDigit;
}


int NumberOf1Between1AndN_Solution2(int n)
{
	if (n <= 0)
		return 0;

	// 将数字写入字符数组中
	char str[50];
	sprintf(str, "%d", n);

	return NumberOf1(str);
}


// ====================测试代码====================
void Test(const char* testName, int n, int expected)
{
	if (testName != nullptr)
		printf("%s begins: \n", testName);


	if (NumberOf1Between1AndN_Solution2(n) == expected)
		printf("Solution2 passed.\n");
	else
		printf("Solution2 failed.\n");

	printf("\n");
}



void Test()
{
	Test("Test1", 1, 1);
	Test("Test2", 5, 1);
	Test("Test3", 10, 2);
	Test("Test4", 55, 16);
	Test("Test5", 99, 20);
	Test("Test6", 10000, 4001);
	Test("Test7", 21345, 18821);
	Test("Test8", 0, 0);
}

int main(int argc, char* argv[])
{
	Test();

	return 0;
}