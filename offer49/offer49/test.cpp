#include <iostream>
#include <vector>
using namespace std;

// 方法一
bool isUgly(int number)
{
	while (number % 2 == 0)
		number /= 2;
	while (number % 3 == 0)
		number /= 3;
	while (number % 5 == 0)
		number /= 5;
	return (number == 1) ? true : false;
}

int GetUglyNumber_Solution1(int index)
{
	if (index <= 0)
		return 0;
	int ulgyNumber = 0;
	int i = 0;
	while (ulgyNumber < index)
	{
		++i;
		if (isUgly(i))
			++ulgyNumber;
	}
	return i;
}

// 方法二
int min(int n1, int n2, int n3)
{
	int ret = (n1 < n2) ? n1 : n2;
	ret = ret < n3 ? ret : n3;
	return ret;
}


int GetUglyNumber_Solution2(int n)
{
#if 0
	if (index <= 0)
		return 0;
	int* nums = new int[index];
	int* p2 = nums;
	int* p3 = nums;
	int* p5 = nums;

	nums[0] = 1;
	int nextUglyIndex = 1;

	while (nextUglyIndex < index)
	{
		// 计算下一个最小的丑数
		int minNumber = min(*p2 * 2, *p3 * 3, *p5 * 5);

		// 将丑数放在next位置
		nums[nextUglyIndex] = minNumber;

		// 对于小于下一个位置的丑数的都在前面存在了
		// 大于的则需要比较，下一个位置放较小的
		while (*p2 * 2 <= nums[nextUglyIndex])
			++p2;
		while (*p3 * 3 <= nums[nextUglyIndex])
			++p3;
		while (*p5 * 5 <= nums[nextUglyIndex])
			++p5;
		++nextUglyIndex;
	}
	return nums[nextUglyIndex - 1];

#endif
	if (n <= 0)
		return 0;

	std::vector<int> vec(n);
	vec[0] = 1;
	int nextIndex = 1;
	int p2 = 0;
	int p3 = 0;
	int p5 = 0;
	while (nextIndex < n)
	{
		int num = min(vec[p2]*2, vec[p3]*3, vec[p5]*5);
		vec[nextIndex] = num;

		while (vec[p2]*2 <= vec[nextIndex])
			++p2;
		while (vec[p3]*3 <= vec[nextIndex])
			++p3;
		while (vec[p5]*5 <= vec[nextIndex])
			++p5;
		++nextIndex;
	}
	return vec[nextIndex - 1];
}

// ====================测试代码====================
void Test(int index, int expected)
{
	if (GetUglyNumber_Solution1(index) == expected)
		printf("solution1 passed\n");
	else
		printf("solution1 failed\n");

	if (GetUglyNumber_Solution2(index) == expected)
		printf("solution2 passed\n");
	else
		printf("solution2 failed\n");
}

int main(int argc, char* argv[])
{
	Test(1, 1);

	Test(2, 2);
	Test(3, 3);
	Test(4, 4);
	Test(5, 5);
	Test(6, 6);
	Test(7, 8);
	Test(8, 9);
	Test(9, 10);
	Test(10, 12);
	Test(11, 15);

	Test(1500, 859963392);

	Test(0, 0);

	return 0;
}