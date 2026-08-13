class Solution {
public:

	vector<int> vis;

	void dfs(vector<int>& nums, vector<int>& perm, int n, vector<vector<int>>& ret)
	{
		if (perm.size() == n){
			ret.push_back(perm);
			return;
		}
		for (int i = 0; i < n; ++i){
			if (vis[i] || i > 0 && nums[i] == nums[i - 1] && !vis[i - 1]){
				continue;
			}
			perm.push_back(nums[i]);
			vis[i] = 1;
			dfs(nums, perm, n, ret);
			vis[i] = 0;
			perm.pop_back();
		}
	}

	vector<vector<int>> permuteUnique(vector<int>& nums) {
		int n = nums.size();
		vector<vector<int>> ret;
		vector<int> prem;
		vis.resize(n);
		sort(nums.begin(), nums.end());
		dfs(nums, prem, n, ret);
		return ret;
	}
};