//判断回文数：给你一个整数 `x` ，如果 `x` 是一个回文整数，返回 `true` ；
//否则，返回 `false` 。回文数是指正序（从左向右）和倒序（从右向左）读都是一样的整数。例如，`121` 是回文，而 `123` 不是。
//
//输入：x = 12321  输出：true
//
//输入：x = 10   输出：false
//
//输入：x = -101  输出：false
//
//请不要将整数转为字符串来解决这个问题。


#include <iostream>
#include <vector>

bool func(int number)
{
	if (number < 0)
		return false;

	std::vector<int> vec;
	int temp = number;
	while (temp)
	{
		vec.push_back(temp % 10);
		temp /= 10;
	}

	int len = vec.size();
	int left = 0;
	int right = len - 1;
	while (left < right)
	{
		if (vec[left] != vec[right])
			return false;
		++left, --right;
	}
	return true;
}

int main()
{
	std::cout << func(121) << std::endl;
	std::cout << func(-121) << std::endl;
	std::cout << func(321) << std::endl;
	return 0;
}