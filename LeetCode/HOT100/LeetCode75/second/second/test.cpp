class Solution {
public:
	void sortColors(vector<int>& nums) {
		int len = nums.size();
		int p0 = 0, p2 = len - 1;
		for (int i = 0; i <= p2; ++i)
		{
			// 用while是因为当i位置是2，而且p2位置也是2的情况
			while (i < p2 && nums[i] == 2)
			{
				swap(nums[i], nums[p2]);
				--p2;
			}
			if (nums[i] == 0)
			{
				swap(nums[p0], nums[i]);
				++p0;
			}
		}
	}
};
