#include <stdio.h>
#include <cstring>
#include <iostream>

char FirstNotRepeatingChar(const char* pString)
{
	if (pString == nullptr)
		return '\0';

	const int hashSize = 256;
	unsigned int hashTable[hashSize];

	for (int i = 0; i < 256; ++i)
		hashTable[i] = 0;

	const char* scan = pString;
	while (*scan != '\0')
	{
		hashTable[*scan]++;
		++scan;
	}

	scan = pString;
	while (*scan != '\0')
	{
		if (hashTable[*scan] == 1)
			return *scan;
		scan++;
	}

	return '\0';
}


// ====================测试代码====================
void Test(const char* pString, char expected)
{
	if (FirstNotRepeatingChar(pString) == expected)
		printf("Test passed.\n");
	else
		printf("Test failed.\n");
}

int main(int argc, char* argv[])
{
	// 常规输入测试，存在只出现一次的字符
	Test("google", 'l');

	// 常规输入测试，不存在只出现一次的字符
	Test("aabccdbd", '\0');

	// 常规输入测试，所有字符都只出现一次
	Test("abcdefg", 'a');

	// 鲁棒性测试，输入nullptr
	Test(nullptr, '\0');

	return 0;
}
