class Solution {
public:
	void twoSum(vector<int>& nums, int flag, int target, int first, vector<vector<int>>& result)
	{
		if (nums.size() - flag < 3)
			return;

		int l = flag + 1;
		int r = nums.size() - 1;
		while (l < r)
		{
			int left = nums[l];
			int right = nums[r];
			int sum = left + right;
			if (sum > target)
			{
				while (l < r && nums[r] == right)
					r--;
			}
			else if (sum < target)
			{
				while (l < r && nums[l] == left)
					l++;
			}
			else
			{
				result.push_back({ first, nums[l], nums[r] });
				while (l < r && nums[r] == right)
					r--;
				while (l < r && nums[l] == left)
					l++;
			}
		}
	}

	vector<vector<int>> threeSum(vector<int>& nums) {
		vector<vector<int>> result;
		int n = nums.size();

		if (n < 3)
			return result;
		sort(nums.begin(), nums.end());

		for (int i = 0; i < n - 2; ++i) // 三个数字，所以可以少遍历两次
		{
			twoSum(nums, i, -nums[i], nums[i], result);
			// 也要处理nums[i]和nums[i+1]相同的情况
			while (i < n - 2 && nums[i] == nums[i + 1])
				i++;
		}
		return result;
	}
};