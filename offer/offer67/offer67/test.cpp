#include<iostream>

long long StrToIntCore(const char* str, bool minus);

enum Status{KValid=0, KInVaild};
int g_Status = KValid;


int StrToInt(const char* str)
{
	g_Status = KInVaild;
	long long num = 0;
	if (str != nullptr && *str != '\0')
	{
		bool minus = false;
		if (*str == '+')
		{
			++str;
		}
		else if (*str == '-')
		{
			++str, minus = true;
		}
		if (*str != '\0')
		{
			num = StrToIntCore(str, minus);
		}
	}

	return (int)num;
}

long long StrToIntCore(const char* str, bool minus)
{
	long long num = 0;

	while (*str != '\0')
	{
		if (*str >= '0' && *str <= '9')
		{
			int flag = minus ? -1 : 1;
			num = num * 10 + flag*(*str - '0');

			// 考虑溢出
			if (!minus && num > 0x7FFFFFFF || minus && num < (signed int)0x80000000)
			{
				num = 0;
				break;
			}
			++str;
		}
		else
		{
			num = 0;
			break;
		}
	}

	// 如果字符转换完毕，将非法字符的标志位改正
	if (*str == '\0')
	{
		g_Status = KValid;
	}
	return num;
}

// ====================测试代码====================
void Test(const char* string)
{
	int result = StrToInt(string);
	if (result == 0 && g_Status == KInVaild)
		printf("the input %s is invalid.\n", string);
	else
		printf("number for %s is: %d.\n", string, result);
}

int main(int argc, char* argv[])
{
	Test(nullptr);

	Test("");

	Test("123");

	Test("+123");

	Test("-123");

	Test("1a33");

	Test("+0");

	Test("-0");

	//有效的最大正整数, 0x7FFFFFFF
	Test("+2147483647");

	Test("-2147483647");

	Test("+2147483648");

	//有效的最小负整数, 0x80000000
	Test("-2147483648");

	Test("+2147483649");

	Test("-2147483649");

	Test("+");

	Test("-");

	return 0;
}