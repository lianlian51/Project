class Solution {
public:
	void nextPermutation(vector<int>& nums) {
		// 1.从尾部开始遍历，然后找到升序的数字
		int i = nums.size() - 2;
		while (i >= 0 && nums[i] >= nums[i + 1])
			--i;

		if (i >= 0)
		{
			// 2.找到第一个较大的数字
			int j = nums.size() - 1;
			while (j >= 0 && nums[i] >= nums[j])
				j--;

			swap(nums[i], nums[j]);
		}
		// 3.反转i之后降序的数字
		reverse(nums.begin() + i + 1, nums.end());
	}
};