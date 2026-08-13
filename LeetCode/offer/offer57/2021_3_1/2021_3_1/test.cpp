class Solution {
public:
	vector<vector<int>> findContinuousSequence(int target) {
		vector<vector<int>> vec;
		vector<int> res;
		int limit = (target - 1) / 2;
		int sum = 0;
		// 从1开始，对数字叠加，直至相等
		for (int i = 1; i <= limit; i++)
		{
			for (int j = i;; j++)
			{
				sum += j;
				if (sum > target)
				{
					sum = 0;
					break;
				}
				else if (sum == target)
				{
					// 清理之前的存储的数字
					res.clear();
					for (int k = i; k <= j; k++)
					{
						res.emplace_back(k);
					}
					vec.emplace_back(res);
					sum = 0;
					break;
				}
			}
		}
		return vec;
	}
};