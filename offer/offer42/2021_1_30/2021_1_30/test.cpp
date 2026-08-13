// 输入一个整型数组，数组中的一个或连续多个整数组成一个子数组。求所有子数组的和的最大值。

class Solution {
public:
	int maxSubArray(vector<int>& nums) {
		int n = nums.size();
		int maxSum = nums[0];

		for (int i = 1; i < n; ++i)
		{
			if (nums[i - 1] > 0)
			{
				nums[i] += nums[i - 1];
			}
			maxSum = max(maxSum, nums[i]);
		}
		return maxSum;
	}
};