class Solution {
public:
	vector<int> getRow(int rowIndex) {
		vector<vector<int>> nums(rowIndex + 1);
		for (int i = 0; i < nums.size(); ++i){
			nums[i].resize(i + 1, 1);
			for (int j = 1; j < nums[i].size() - 1; ++j){
				nums[i][j] = nums[i - 1][j] + nums[i - 1][j - 1];
			}
		}
		vector<int> ret;
		for (int i = 0; i <= rowIndex; ++i){
			ret.push_back(nums[rowIndex][i]);
		}
		return ret;
	}
};