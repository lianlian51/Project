#include <iostream>

int g_max = 10;
char* g_str1 = new char[2 * g_max + 1];
char* g_str2 = new char[2 * g_max + 1];

int compare(const void* strnumber1, const void* strnumber2);

void PrintMinNumber(int* number, int length)
{
	if (number == nullptr || length <= 0)
		return;

	// 1.将数组写入到二级指针数组中
	char** strNumber = (char**)(new int[length]);
	for (int i = 0; i < length; ++i)
	{
		strNumber[i] = new char[g_max + 1];
		sprintf(strNumber[i], "%d", number[i]);
	}

	// 2.比较数字的大小
	qsort(strNumber, length, sizeof(char*), compare);

	// 3.打印
	for (int i = 0; i < length; ++i)
	{
		printf("%s", strNumber[i]);
	}
	printf("\n");

	// 4.销毁
	for (int i = 0; i < length; ++i)
	{
		delete strNumber[i];
	}
	delete strNumber;
}

// 将两个字符串拼接起来，比较大小
int compare(const void* strnumber1, const void* strnumber2)
{
	strcpy(g_str1, *(char**)strnumber1);
	strcat(g_str1, *(char**)strnumber2);

	strcpy(g_str2, *(char**)strnumber2);
	strcat(g_str2, *(char**)strnumber1);

	return strcmp(g_str1, g_str2);
}

// ====================测试代码====================
void Test(const char* testName, int* numbers, int length, const char* expectedResult)
{
	if (testName != nullptr)
		printf("%s begins:\n", testName);

	if (expectedResult != nullptr)
		printf("Expected result is: \t%s\n", expectedResult);

	printf("Actual result is: \t");
	PrintMinNumber(numbers, length);

	printf("\n");
}

void Test1()
{
	int numbers[] = { 3, 5, 1, 4, 2 };
	Test("Test1", numbers, sizeof(numbers) / sizeof(int), "12345");
}

void Test2()
{
	int numbers[] = { 3, 32, 321 };
	Test("Test2", numbers, sizeof(numbers) / sizeof(int), "321323");
}

void Test3()
{
	int numbers[] = { 3, 323, 32123 };
	Test("Test3", numbers, sizeof(numbers) / sizeof(int), "321233233");
}

void Test4()
{
	int numbers[] = { 1, 11, 111 };
	Test("Test4", numbers, sizeof(numbers) / sizeof(int), "111111");
}

// 数组中只有一个数字
void Test5()
{
	int numbers[] = { 321 };
	Test("Test5", numbers, sizeof(numbers) / sizeof(int), "321");
}

void Test6()
{
	Test("Test6", nullptr, 0, "Don't print anything.");
}


int main()
{
	Test1();
	Test2();
	Test3();
	Test4();
	Test5();
	Test6();

	return 0;
}