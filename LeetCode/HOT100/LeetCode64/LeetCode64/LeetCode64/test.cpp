class Solution {
public:
	int minPathSum(vector<vector<int>>& grid) {
		int m = grid.size();
		int n = grid[0].size();
		vector<vector<int>> res(m + 1, vector<int>(n + 1, 0));
		res[1][1] = grid[0][0];
		for (int i = 1; i < m + 1; ++i)
		{
			for (int j = 1; j < n + 1; ++j)
			{
				int tmp = grid[i - 1][j - 1];
				if (i == 1 && j == 1)
					continue;
				else if (i == 1)
				{
					tmp += res[i][j - 1];
				}
				else if (j == 1)
				{
					tmp += res[i - 1][j];
				}
				else
					tmp += min(res[i - 1][j], res[i][j - 1]);
				res[i][j] = tmp;
			}
		}
		return res[m][n];
	}
};