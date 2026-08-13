class Solution {
public:
	vector<int> spiralOrder(vector<vector<int>>& matrix) {
		if (matrix.size() == 0 || matrix[0].size() == 0) {
			return{};
		}

		vector<int> ans;
		int m = matrix.size();
		int n = matrix[0].size();
		int r1 = 0, r2 = m - 1;
		int c1 = 0, c2 = n - 1;
		while (r1 <= r2 && c1 <= c2){
			for (int i = c1; i <= c2; ++i){
				ans.push_back(matrix[r1][i]);
			}

			for (int i = r1 + 1; i <= r2; ++i){
				ans.push_back(matrix[i][c2]);
			}

			if (r1 < r2 && c1 < c2){
				for (int i = c2 - 1; i > c1; --i){
					ans.push_back(matrix[r2][i]);
				}
				for (int i = r2; i > r1; --i){
					ans.push_back(matrix[i][c1]);
				}
			}
			r1++; c2--; r2--; c1++;
		}
		return ans;
	}
};