// 牛客网：最难的问题
// 运算优于查表，查表优于判断

#include <stdio.h>

int main()
{
	int c;
	while ((c = getchar()) != EOF)
	{
		if ('A' <= c)
			c = 'E' < c ? (c - 5) : (c + 21);
		putchar(c);
	}

	return 0;
}