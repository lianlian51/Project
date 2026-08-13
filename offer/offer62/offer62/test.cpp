#include <iostream>
#include <list>

int LastRemaining_Solution1(unsigned int n, unsigned int m)
{
	if (m < 1 || n < 1)
		return -1;

	std::list<int> l;
	for (int i = 0; i < n; ++i)
		l.push_back(i);

	std::list<int>::iterator current = l.begin();
	while (l.size() > 1)
	{
		for (int i = 1; i < m; ++i)
		{
			++current;
			if (current == l.end())
				current = l.begin();
		}
		std::list<int>::iterator next = ++current;
		if (next == l.end())
			next = l.begin();
		--current;
		l.erase(current);
		current = next;
	}
	return *(current);
}

int LastRemaining_Solution2(unsigned int n, unsigned int m)
{
	if (m < 1 || n < 1)
		return -1;

	int last = 0;
	for (int i = 2; i <= n; ++i)
	{
		last = (last + m) % i;
	}
	return last;
}


// ====================²âÊÔ´úÂë====================
void Test(const char* testName, unsigned int n, unsigned int m, int expected)
{
	if (testName != nullptr)
		printf("%s begins: \n", testName);

	if (LastRemaining_Solution1(n, m) == expected)
		printf("Solution1 passed.\n");
	else
		printf("Solution1 failed.\n");

	if (LastRemaining_Solution2(n, m) == expected)
		printf("Solution2 passed.\n");
	else
		printf("Solution2 failed.\n");

	printf("\n");
}

void Test1()
{
	Test("Test1", 5, 3, 3);
}

void Test2()
{
	Test("Test2", 5, 2, 2);
}

void Test3()
{
	Test("Test3", 6, 7, 4);
}

void Test4()
{
	Test("Test4", 6, 6, 3);
}

void Test5()
{
	Test("Test5", 0, 0, -1);
}

void Test6()
{
	Test("Test6", 4000, 997, 1027);
}

int main(int argc, char* argv[])
{
	Test1();
	Test2();
	Test3();
	Test4();
	Test5();
	Test6();

	return 0;
}