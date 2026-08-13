class Solution {
public:
	vector<int> twoSum(vector<int>& nums, int target) {
		int left = 0;
		int right = nums.size() - 1;
		while (left < right)
		{
			int num = nums[left] + nums[right];
			if (num < target)
			{
				++left;
			}
			else if (num > target)
			{
				--right;
			}
			else
			{
				return vector<int> {nums[left], nums[right]};
			}
		}
		return vector<int> {};
	}
};