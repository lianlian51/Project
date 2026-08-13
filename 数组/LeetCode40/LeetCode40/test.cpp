class Solution {
public:
	vector<vector<int>> res;
	vector<int> temp;

	void dfs(vector<int>& candidates, int target, int index)
	{
		if (target == 0){
			// 这里target减到0，则表示存在这个数组和等于目标值
			res.push_back(temp);
			return;
		}

		for (int i = index; i < candidates.size() && target - candidates[i] >= 0; ++i){
			if (i > index && candidates[i] == candidates[i - 1]){ // 处理重复的数字
				continue;
			}
			temp.push_back(candidates[i]);
			dfs(candidates, target - candidates[i], i + 1); // 减掉当前值，继续回溯
			temp.pop_back();
		}
	}

	vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
		sort(candidates.begin(), candidates.end());
		dfs(candidates, target, 0);
		return res;
	}
};

