class Solution {
public:
	int maximalRectangle(vector<vector<char>>& matrix) {
		int m = matrix.size();
		// 判空
		if (m == 0)
			return 0;
		int n = matrix[0].size();

		// 开辟二维数组，记录之后单调栈的结果
		vector<vector<int>> nums(m, vector<int>(n, 0));
		for (int i = 0; i < m; ++i){
			for (int j = 0; j < n; ++j){
				if (matrix[i][j] == '1'){
					// 将第一行置为1
					nums[i][j] = (j == 0 ? 0 : nums[i][j - 1]) + 1;
				}
			}
		}

		// 对每一列进行单调栈
		int ret = 0;
		for (int j = 0; j < n; ++j){
			// 注意：这里的是操作的是列，要注意开辟空间的大小
			vector<int> up(m, 0), down(m, 0);
			stack<int> stk;

			// 将一列的上边界记录下来
			for (int i = 0; i < m; ++i){
				while (!stk.empty() && nums[stk.top()][j] >= nums[i][j]){
					stk.pop();
				}
				up[i] = stk.empty() ? -1 : stk.top();
				stk.push(i);
			}

			// 将栈清空
			stk = stack<int>();
			// 将一列的下边界记录在down中
			for (int i = m - 1; i >= 0; --i){
				while (!stk.empty() && nums[stk.top()][j] >= nums[i][j]){
					stk.pop();
				}
				down[i] = stk.empty() ? m : stk.top();
				stk.push(i);
			}


			for (int i = 0; i < m; ++i){
				int h = down[i] - up[i] - 1;
				int area = h * nums[i][j];
				ret = max(ret, area);
			}
		}
		return ret;
	}
};