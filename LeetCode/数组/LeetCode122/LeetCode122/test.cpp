class Solution {
public:
	int maxProfit(vector<int>& prices) {
		// 动态规划
		int n = prices.size();
		vector<vector<int>> dp(n, vector<int>(2)); // 第一列表示卖出，第二列表示买入
		dp[0][0] = 0, dp[0][1] = -prices[0];
		for (int i = 1; i < n; ++i){
			dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] + prices[i]);
			dp[i][1] = max(dp[i - 1][1], dp[i - 1][0] - prices[i]);
		}
		return dp[n - 1][0];
	}
};


// 方法二
class Solution {
public:
	int maxProfit(vector<int>& prices) {
		int ans = 0;
		int n = prices.size();
		for (int i = 1; i < n; ++i){
			ans += max(0, prices[i] - prices[i - 1]);
		}
		return ans;
	}
};