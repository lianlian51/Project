class Solution {
public:
	int longestConsecutive(vector<int>& nums) {
		// 采用哈希表，unordered_set有去重的功能
		unordered_set<int> nums_set;
		for (auto& num : nums)
			nums_set.insert(num);

		// 返回值
		int longret = 0;
		for (auto& num : nums_set)
		{
			// 如果num- 1存在的话，那么直接跳过，可以减少运行次数
			if (!nums_set.count(num - 1))
			{
				// curnum表示连续的数字
				// curlen 表示连续数字的长度
				int curnum = num;
				int curlen = 1;
				while (nums_set.count(curnum + 1))
				{
					curnum += 1;
					curlen += 1;
				}
				// 更新长度
				longret = max(longret, curlen);
			}
		}
		return longret;
	}
};