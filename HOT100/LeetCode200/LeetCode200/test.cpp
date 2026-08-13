class Solution {
private:
	void dfs(std::vector<std::vector<char>>& grid, int row, int col)
	{
		int nr = grid.size();
		int nc = grid[0].size();
		grid[row][col] = '0';
		if (row - 1 >= 0 && grid[row - 1][col] == '1') dfs(grid, row - 1, col);
		if (row + 1 < nr && grid[row + 1][col] == '1') dfs(grid, row + 1, col);
		if (col - 1 >= 0 && grid[row][col - 1] == '1') dfs(grid, row, col - 1);
		if (col + 1 < nc && grid[row][col + 1] == '1') dfs(grid, row, col + 1);
	}

public:
	int numIslands(vector<vector<char>>& grid) {
		int row = grid.size();
		if (row <= 0)
			return 0;

		int ans = 0;
		int col = grid[0].size();
		for (int i = 0; i < row; ++i)
		{
			for (int j = 0; j < col; ++j)
			{
				if (grid[i][j] == '1')
				{
					ans++;
					dfs(grid, i, j);
				}
			}
		}
		return ans;
	}
};