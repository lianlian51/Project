//#include <iostream>
//
//int Compare(const void *arg1, const void *arg2);
//
//bool IsContinuous(int* numbers, int length)
//{
//	if (numbers == nullptr || length <= 0)
//		return false;
//
//	qsort(numbers, length, sizeof(int), Compare);
//
//	// 1.统计0的个数
//	int numberOf0 = 0;
//	for (int i = 0; i < length && numbers[i] == 0; ++i)
//		++numberOf0;
//
//	// 2.统计间隔的个数
//	int numberOfGap = 0;
//	int small = numberOf0;
//	int big = small + 1;
//	while (big < length)
//	{
//		if (numbers[big] == numbers[small])
//			return false;
//		numberOfGap += numbers[big] - numbers[small] - 1;
//		small = big;
//		++big;
//	}
//
//	// 如果0个数大于间隔，则返回true，否则返回false
//	return numberOf0 >= numberOfGap ? true : false;
//}
//
//int Compare(const void *arg1, const void *arg2)
//{
//	return *(int*)arg1 - *(int*)arg2;
//}
//
//// ====================测试代码====================
//void Test(const char* testName, int* numbers, int length, bool expected)
//{
//	if (testName != nullptr)
//		printf("%s begins: ", testName);
//
//	if (IsContinuous(numbers, length) == expected)
//		printf("Passed.\n");
//	else
//		printf("Failed.\n");
//}
//
//void Test1()
//{
//	int numbers[] = { 1, 3, 2, 5, 4 };
//	Test("Test1", numbers, sizeof(numbers) / sizeof(int), true);
//}
//
//void Test2()
//{
//	int numbers[] = { 1, 3, 2, 6, 4 };
//	Test("Test2", numbers, sizeof(numbers) / sizeof(int), false);
//}
//
//void Test3()
//{
//	int numbers[] = { 0, 3, 2, 6, 4 };
//	Test("Test3", numbers, sizeof(numbers) / sizeof(int), true);
//}
//
//void Test4()
//{
//	int numbers[] = { 0, 3, 1, 6, 4 };
//	Test("Test4", numbers, sizeof(numbers) / sizeof(int), false);
//}
//
//void Test5()
//{
//	int numbers[] = { 1, 3, 0, 5, 0 };
//	Test("Test5", numbers, sizeof(numbers) / sizeof(int), true);
//}
//
//void Test6()
//{
//	int numbers[] = { 1, 3, 0, 7, 0 };
//	Test("Test6", numbers, sizeof(numbers) / sizeof(int), false);
//}
//
//void Test7()
//{
//	int numbers[] = { 1, 0, 0, 5, 0 };
//	Test("Test7", numbers, sizeof(numbers) / sizeof(int), true);
//}
//
//void Test8()
//{
//	int numbers[] = { 1, 0, 0, 7, 0 };
//	Test("Test8", numbers, sizeof(numbers) / sizeof(int), false);
//}
//
//void Test9()
//{
//	int numbers[] = { 3, 0, 0, 0, 0 };
//	Test("Test9", numbers, sizeof(numbers) / sizeof(int), true);
//}
//
//void Test10()
//{
//	int numbers[] = { 0, 0, 0, 0, 0 };
//	Test("Test10", numbers, sizeof(numbers) / sizeof(int), true);
//}
//
//// 有对子
//void Test11()
//{
//	int numbers[] = { 1, 0, 0, 1, 0 };
//	Test("Test11", numbers, sizeof(numbers) / sizeof(int), false);
//}
//
//// 鲁棒性测试
//void Test12()
//{
//	Test("Test12", nullptr, 0, false);
//}
//
//int main(int argc, char* argv[])
//{
//	Test1();
//	Test2();
//	Test3();
//	Test4();
//	Test5();
//	Test6();
//	Test7();
//	Test8();
//	Test9();
//	Test10();
//	Test11();
//	Test12();
//
//	return 0;
//}
#include <iostream>
using namespace std;
#include <string>

void func(string s)
{}
int main()
{
	int test = 1234;
	//printf("%s, %5.3s, %2d\n", "Hithink", "Hithink", test);
	func("ab");
	return 0;
}