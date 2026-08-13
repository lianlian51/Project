#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


	int rob(vector<int>& nums) {
		int ans = 0;
		int size = nums.size();
		if (size == 0)
			return 0;
		if (size == 1)
			return nums[0];
		std::vector<int> dp(size, 0);
		dp[0] = nums[0];
		dp[1] = max(nums[0], nums[1]);
		for (int i = 2; i < size; ++i)
		{
			dp[i] = max(nums[i] + dp[i - 2], dp[i - 1]);
		}
		return dp[size - 1];
}





int main()
{
	std::vector<int> vec{ 2, 1, 1, 2 };
	std::cout << rob(vec) << std::endl;
	return 0;
}

int rob(std::vector<int> nums)
{
	if (nums.empty())
		return 0;
	if (nums.size() == 1)
		return nums[0];

	int first = nums[0], second = max(nums[0], nums[1]);
	for (int i = 2; i < nums.size(); ++i)
	{
		int temp = second;
		second = max(nums[i] + first, second);
		first = temp;
	}
	return second;
}
