#include <iostream>

class CharStatistics
{
public:
	CharStatistics()
	:index(0)
	{
		for (int i = 0; i < 256; ++i)
		{
			vec[i] = -1;
		}
	}

	void Insert(char ch)
	{
		if (vec[ch] == -1)
			vec[ch] = index;
		else if (vec[ch] >= 0)
			vec[ch] = -2;
		++index;
	}

	char FirstAppearingOnce()
	{
		char ch = '\0';
		int minIndex = INT_MAX;
		for (int i = 0; i < 256; ++i)
		{
			if (vec[i] >= 0 && minIndex > vec[i])
			{
				ch = (char)i;
				minIndex = vec[i];
			}
		}
		return ch;
	}

	// -1: 代表没有出现
	// -2: 出现了次数超过了一次

private:
	int vec[256];
	int index;
};


// ====================测试代码====================
void Test(const char* testName, CharStatistics chars, char expected)
{
	if (testName != nullptr)
		printf("%s begins: ", testName);

	if (chars.FirstAppearingOnce() == expected)
		printf("Passed.\n");
	else
		printf("FAILED.\n");
}

int main(int argc, char* argv[])
{
	CharStatistics chars;

	Test("Test1", chars, '\0');

	chars.Insert('g');
	Test("Test2", chars, 'g');

	chars.Insert('o');
	Test("Test3", chars, 'g');

	chars.Insert('o');
	Test("Test4", chars, 'g');

	chars.Insert('g');
	Test("Test5", chars, '\0');

	chars.Insert('l');
	Test("Test6", chars, 'l');

	chars.Insert('e');
	Test("Test7", chars, 'l');

	return 0;
}