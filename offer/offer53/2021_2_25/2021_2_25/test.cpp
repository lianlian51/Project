class Solution {
public:
	int missingNumber(vector<int>& nums) {
		int n = nums.size();
		int l = 0;
		int r = n - 1;
		int m = (l + r) >> 1;
		while (l <= r)
		{
			if (nums[m] == m)
			{
				l = m + 1;
			}
			else
			{
				r = m - 1;
			}
			m = (l + r) >> 1;
		}

		return l;
	}
};
