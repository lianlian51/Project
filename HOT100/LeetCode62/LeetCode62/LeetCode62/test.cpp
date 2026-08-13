class Solution {
public:
	int uniquePaths(int m, int n) {
		vector<vector<int>> res(m + 1);
		for (int i = 0; i < m + 1; ++i)
		{
			res[i].resize(n + 1);
		}
		res[0][1] = 1;
		for (int i = 1; i < m + 1; ++i)
		{
			for (int j = 1; j < n + 1; ++j)
			{
				res[i][j] = res[i][j - 1] + res[i - 1][j];
			}
		}
		return res[m][n];
	}
};