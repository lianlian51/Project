#include <iostream>
#include <string>
#include <vector>


int longestSubstringWithoutDuplication_2(const std::string& str)
{
	if (str.size() <= 0)
		return 0;

	int curLength = 0;
	int maxLength = 0;
	std::vector<int> vec(26);
	for (int i = 0; i < 26; ++i)
		vec[i] = -1;

	for (int i = 0; i < str.size(); ++i)
	{
		int preIndex = vec[str[i] - 'a'];
		if (preIndex < 0 || i - preIndex > curLength)
			++curLength;
		else
		{
			if (curLength > maxLength)
				maxLength = curLength;

			curLength = i - preIndex;
		}
		vec[str[i] - 'a'] = i;
	}
	if (curLength > maxLength)
		maxLength = curLength;
	return maxLength;
}

// 方法一：蛮力法
bool hasDuplication(const std::string& str, int position[]);

int longestSubstringWithoutDuplication_1(const std::string& str)
{
	int longest = 0;
	int* position = new int[26];
	for (int start = 0; start < str.length(); ++start)
	{
		for (int end = start; end < str.length(); ++end)
		{
			int count = end - start + 1;
			const std::string& substring = str.substr(start, count);
			if (!hasDuplication(substring, position))
			{
				if (count > longest)
					longest = count;
			}
			else
				break;

		}
	}

	delete[] position;
	return longest;
}

bool hasDuplication(const std::string& str, int position[])
{
	for (int i = 0; i < 26; ++i)
		position[i] = -1;

	for (int i = 0; i < str.length(); ++i)
	{
		int indexInPosition = str[i] - 'a';
		if (position[indexInPosition] >= 0)
			return true;

		position[indexInPosition] = indexInPosition;
	}

	return false;
}


// ====================测试代码====================
void testSolution1(const std::string& input, int expected)
{
	int output = longestSubstringWithoutDuplication_1(input);
	if (output == expected)
		std::cout << "Solution 1 passed, with input: " << input << std::endl;
	else
		std::cout << "Solution 1 FAILED, with input: " << input << std::endl;
}

void testSolution2(const std::string& input, int expected)
{
	int output = longestSubstringWithoutDuplication_2(input);
	if (output == expected)
		std::cout << "Solution 2 passed, with input: " << input << std::endl;
	else
		std::cout << "Solution 2 FAILED, with input: " << input << std::endl;
}

void test(const std::string& input, int expected)
{
	testSolution1(input, expected);
	testSolution2(input, expected);
}

void test1()
{
	const std::string input = "abcacfrar";
	int expected = 4;
	test(input, expected);
}

void test2()
{
	const std::string input = "acfrarabc";
	int expected = 4;
	test(input, expected);
}

void test3()
{
	const std::string input = "arabcacfr";
	int expected = 4;
	test(input, expected);
}

void test4()
{
	const std::string input = "aaaa";
	int expected = 1;
	test(input, expected);
}

void test5()
{
	const std::string input = "abcdefg";
	int expected = 7;
	test(input, expected);
}

void test6()
{
	const std::string input = "aaabbbccc";
	int expected = 2;
	test(input, expected);
}

void test7()
{
	const std::string input = "abcdcba";
	int expected = 4;
	test(input, expected);
}

void test8()
{
	const std::string input = "abcdaef";
	int expected = 6;
	test(input, expected);
}

void test9()
{
	const std::string input = "a";
	int expected = 1;
	test(input, expected);
}

void test10()
{
	const std::string input = "";
	int expected = 0;
	test(input, expected);
}

int main(int argc, char* argv[])
{
	test1();
	test2();
	test3();
	test4();
	test5();
	test6();
	test7();
	test8();
	test9();
	test10();

	return 0;
}