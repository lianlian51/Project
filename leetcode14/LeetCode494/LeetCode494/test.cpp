class Solution {
public:
	int count;
	int findTargetSumWays(vector<int>& nums, int target) {
		// »ØËİ
		backtrack(nums, target, 0, 0);
		return count;
	}

	void backtrack(vector<int>& nums, int target, int index, int num)
	{
		if (index == nums.size())
		{
			if (num == target)
				count++;
		}
		else
		{
			backtrack(nums, target, index + 1, num + nums[index]);
			backtrack(nums, target, index + 1, num - nums[index]);
		}
	}
};