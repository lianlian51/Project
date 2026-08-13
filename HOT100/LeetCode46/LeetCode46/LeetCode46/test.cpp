class Solution {
public:
	void dfs(vector<vector<int>>& res, vector<int>& output, int first, int len)
	{
		if (first == len)
		{
			res.emplace_back(output);
			return;
		}

		for (int i = first; i < len; ++i)
		{
			swap(output[first], output[i]);
			dfs(res, output, first + 1, len);
			swap(output[first], output[i]);
		}
	}

	vector<vector<int>> permute(vector<int>& nums) {
		vector<vector<int>> res;
		dfs(res, nums, 0, nums.size());
		return res;
	}
};