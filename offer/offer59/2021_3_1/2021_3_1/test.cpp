class Solution {
public:
	vector<int> maxSlidingWindow(vector<int>& nums, int k) {
		vector<int> v;
		if (nums.size() == 0)
			return v;
		if (nums.size() == 1)
		{
			v.push_back(nums[0]);
			return v;
		}
		if (nums.size() <= k)
		{
			int tmp = nums[0];
			for (int i = 1; i < nums.size(); ++i)
			{
				if (nums[i] > tmp)
				{
					tmp = nums[i];
				}
			}
			v.push_back(tmp);
			return v;
		}
		for (int i = 0; i < nums.size() - k + 1; ++i)
		{
			int tmp = nums[i];
			for (int j = 1; j < k; ++j)
			{
				if (nums[i + j] > tmp)
				{
					tmp = nums[i + j];
				}
			}
			v.push_back(tmp);
		}
		// sort(v.begin(), v.end());
		return v;
	}
};