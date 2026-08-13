class Solution {
public:
	int m, n;

	void dfs(vector<vector<char>>& board, int i, int j){
		if (i < 0 || j < 0 || i >= m || j >= n || board[i][j] != 'O'){ // 这里要设置为不等于O，因为字符A是可以相互连接的
			return;
		}
		board[i][j] = 'A'; // 检测边缘的旁边有没有O
		dfs(board, i + 1, j);
		dfs(board, i - 1, j);
		dfs(board, i, j + 1);
		dfs(board, i, j - 1);
	}

	void solve(vector<vector<char>>& board) {
		m = board.size();
		n = board[0].size();
		// 检测矩阵边缘是不是有O
		for (int i = 0; i < m; ++i){
			dfs(board, i, 0);
			dfs(board, i, n - 1);
		}
		for (int i = 0; i < n; ++i){
			dfs(board, 0, i);
			dfs(board, m - 1, i);
		}
		for (int i = 0; i < m; ++i){
			for (int j = 0; j < n; ++j){
				if (board[i][j] == 'O'){
					board[i][j] = 'X';
				}
				else if (board[i][j] == 'A'){
					board[i][j] = 'O';
				}
			}
		}
	}
};