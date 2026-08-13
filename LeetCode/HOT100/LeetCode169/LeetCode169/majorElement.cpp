class Solution {
public:
	int majorityElement(vector<int>& nums) {
		int count = 0;
		int ans;
		for (int i = 0; i < (int)nums.size(); ++i)
		{
			if (count == 0)
			{
				ans = nums[i];
			}
			if (ans == nums[i])
			{
				count++;
			}
			else
			{
				count--;
			}
		}
		return ans;
	}
};