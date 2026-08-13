class Solution {
public:
	int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
		// 动态规划
		int m = obstacleGrid.size();
		int n = obstacleGrid[0].size();
		vector<int> ret(n);
		ret[0] = (obstacleGrid[0][0] == 0);
		for (int i = 0; i < m; ++i){
			for (int j = 0; j < n; ++j){
				// 处理障碍物
				if (obstacleGrid[i][j] == 1){
					ret[j] = 0;
					continue;
				}
				// 保证j-1合法及obstacleGrid[i][j-1]合法
				if (j - 1 >= 0 && obstacleGrid[i][j - 1] == 0){
					ret[j] += ret[j - 1];
				}
			}
		}
		return ret.back();
	}
};