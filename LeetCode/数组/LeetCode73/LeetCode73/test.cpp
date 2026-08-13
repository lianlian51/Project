class Solution {
public:
	void setZeroes(vector<vector<int>>& matrix) {
		// 双标记法
		int m = matrix.size();
		int n = matrix[0].size();
		int fr = false, fc = false;
		// 确定第一行和第一列是否有0
		for (int i = 0; i < m; ++i){
			if (!matrix[i][0]){
				fr = true;
			}
		}
		for (int i = 0; i < n; ++i){
			if (!matrix[0][i]){
				fc = true;
			}
		}
		// 将除了第一行和第一列中有0的元素的该行和该列的第一个元素置为0
		for (int i = 1; i < m; ++i){
			for (int j = 1; j < n; ++j){
				if (!matrix[i][j]){
					matrix[i][0] = matrix[0][j] = 0;
				}
			}
		}
		// 如果该行或列第一个元素为0，则将该位置置为0
		for (int i = 1; i < m; ++i){
			for (int j = 1; j < n; ++j){
				if (!matrix[i][0] || !matrix[0][j]){
					matrix[i][j] = 0;
				}
			}
		}
		// 将标记的行和列置为0
		for (int i = 0; i < m; ++i){
			if (fr){
				matrix[i][0] = 0;
			}
		}
		for (int i = 0; i < n; ++i){
			if (fc){
				matrix[0][i] = 0;
			}
		}
	}
};