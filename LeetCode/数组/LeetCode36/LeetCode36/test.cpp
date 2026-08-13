class Solution {
public:
	bool isValidSudoku(vector<vector<char>>& board) {
		vector<vector<int>> row(9, vector<int>(9, 0));
		vector<vector<int>> col(9, vector<int>(9, 0));
		vector<vector<int>> body(9, vector<int>(9, 0));

		for (int i = 0; i < 9; ++i){
			for (int j = 0; j < 9; ++j){
				if (board[i][j] == '.'){
					continue;
				}
				int val = board[i][j] - '1';
				int body_index = (i / 3) * 3 + j / 3;
				if (row[i][val] == 0 && col[j][val] == 0 && body[body_index][val] == 0){
					row[i][val] = 1;
					col[j][val] = 1;
					body[body_index][val] = 1;
				}
				else {
					return false;
				}
			}
		}
		return true;
	}
};