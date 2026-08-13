class Solution {
public:
	bool canPartition(vector<int>& nums) {
		int n = nums.size();
		int sum = accumulate(nums.begin(), nums.end(), 0);
		int max = *max_element(nums.begin(), nums.end()); // 剔除最大数大于平均数的情况
		if (sum & 1)
		{
			return false;  // 和为奇数找不到
		}

		int target = sum / 2;
		if (max > target){
			return false;
		}
#if 0
		vector<vector<int>> dp(n, vector<int>(target + 1, 0));
		for (int i = 0; i < n; ++i){
			dp[i][0] = true;
		}

		dp[0][nums[0]] = true;

		for (int i = 1; i < n; ++i)
		{
			int num = nums[i];
			for (int j = 1; j <= target; ++j)
			{
				if (j >= num)
				{
					dp[i][j] = dp[i - 1][j] | dp[i - 1][j - num];
				}
				else {
					dp[i][j] = dp[i - 1][j];
				}
			}
		}
		return dp[n - 1][target];
#endif 
		vector<int> dp(target + 1, 0);
		dp[0] = true;
		for (int i = 0; i < n; ++i)
		{
			int num = nums[i];
			for (int j = target; j >= num; --j)
			{
				dp[j] |= dp[j - num];
			}
		}
		return dp[target];
	}
};