#include <iostream>
#include <string>
using namespace std;

int GetTranslationCount(const std::string & str);


int GetTranslationCount(int num)
{
	if (num < 0)
		return 0;

	std::string s = std::to_string(num);
	return GetTranslationCount(s);
}

int GetTranslationCount(const std::string & str)
{
	int length = str.size();
	int* counts = new int[length];
	int count = 0;
	for (int i = length - 1; i >= 0; --i)
	{
		count = 0;
		if (i < length - 1)
			count = counts[i + 1];
		else
			count = 1;

		if (i < length - 1)
		{
			int num1 = str[i] - '0';
			int num2 = str[i + 1] - '0';
			int sum = num1 * 10 + num2;
			if (sum >= 10 && sum <= 25)
			{
				if (i < length - 2)
					count += counts[i + 2];
				else
					count += 1;
			}
		}
		counts[i] = count;
	}
	count = counts[0];
	delete counts;
	return count;
}

// ====================²âÊÔ´úÂë====================
void Test(const string& testName, int number, int expected)
{
	if (GetTranslationCount(number) == expected)
		cout << testName << " passed." << endl;
	else
		cout << testName << " FAILED." << endl;
}

void Test1()
{
	int number = 0;
	int expected = 1;
	Test("Test1", number, expected);
}

void Test2()
{
	int number = 10;
	int expected = 2;
	Test("Test2", number, expected);
}

void Test3()
{
	int number = 125;
	int expected = 3;
	Test("Test3", number, expected);
}

void Test4()
{
	int number = 126;
	int expected = 2;
	Test("Test4", number, expected);
}

void Test5()
{
	int number = 426;
	int expected = 1;
	Test("Test5", number, expected);
}

void Test6()
{
	int number = 100;
	int expected = 2;
	Test("Test6", number, expected);
}

void Test7()
{
	int number = 101;
	int expected = 2;
	Test("Test7", number, expected);
}

void Test8()
{
	int number = 12258;
	int expected = 5;
	Test("Test8", number, expected);
}

void Test9()
{
	int number = -100;
	int expected = 0;
	Test("Test9", number, expected);
}

int main()
{
	Test1();
	Test2();
	Test3();
	Test4();
	Test5();
	Test6();
	Test7();
	Test8();
	Test9();

	return 0;
}