class Solution {
public:
	int maximalSquare(vector<vector<char>>& matrix) {
		int row = matrix.size();
		int col = matrix[0].size();
		if (row == 0 || col == 0)
			return 0;
		int ans = 0;
		std::vector<std::vector<int>> dp(row, std::vector<int>(col));
		for (int i = 0; i < row; ++i)
		{
			for (int j = 0; j < col; ++j)
			{
				if (matrix[i][j] == '1')
				{
					if (i == 0 || j == 0)
					{
						dp[i][j] = 1;
					}
					else
					{
						dp[i][j] = min(min(dp[i - 1][j], dp[i][j - 1]), dp[i - 1][j - 1]) + 1;
					}
					ans = max(ans, dp[i][j]);
				}
			}
		}
		return ans*ans;
	}
};