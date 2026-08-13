class Solution {
public:
	vector<int> temp;
	vector<vector<int>> ans;

	bool check(int mask, int k, int n){
		temp.clear();
		for (int i = 0; i < 9; ++i){
			if ((1 << i) & mask){
				temp.push_back(i + 1);
			}
		}
		return temp.size() == k && accumulate(temp.begin(), temp.end(), 0) == n;
	}

	vector<vector<int>> combinationSum3(int k, int n) {
		// 二进制子集枚举
		for (int i = 0; i < (1 << 9); ++i){
			if (check(i, k, n)){
				ans.push_back(temp);
			}
		}
		return ans;
	}
};

class Solution {
public:
	vector<int> temp;
	vector<vector<int>> ans;

	void dfs(int cur, int n, int k, int sum)
	{
		if (temp.size() + n - cur + 1 < k || temp.size() > k){
			return;
		}
		if (temp.size() == k && accumulate(temp.begin(), temp.end(), 0) == sum){
			ans.push_back(temp);
			return;
		}
		temp.push_back(cur);
		dfs(cur + 1, n, k, sum);
		temp.pop_back();
		dfs(cur + 1, n, k, sum);
	}

	vector<vector<int>> combinationSum3(int k, int n) {
		// 组合枚举
		dfs(1, 9, k, n);
		return ans;
	}
};