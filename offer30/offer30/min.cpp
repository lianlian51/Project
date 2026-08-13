#include "StackWithMin.h"

void Test(const char* testname, const StackWithMin<int>& stk, int expected)
{
	if (testname != nullptr)
		std::cout << testname << " ";
	if (stk.Min() == expected)
		std::cout << "Pass!!!" << std::endl;
	else
		std::cout << "Failed!!!" << std::endl;
}


void TestStackMin()
{
	StackWithMin<int> stack;

	stack.Push(3);
	Test("Test1", stack, 3);

	stack.Push(4);
	Test("Test2", stack, 3);

	stack.Push(2);
	Test("Test3", stack, 2);

	stack.Push(3);
	Test("Test4", stack, 2);

	stack.Pop();
	Test("Test5", stack, 2);

	stack.Pop();
	Test("Test6", stack, 3);

	stack.Pop();
	Test("Test7", stack, 3);

	stack.Push(0);
	Test("Test8", stack, 0);
}



int main()
{
	TestStackMin();
	return 0;
}