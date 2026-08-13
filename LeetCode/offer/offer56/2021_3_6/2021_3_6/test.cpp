class Solution {
public:
	int singleNumber(vector<int>& nums) {
		// 用两个哈希表来记录，once记录一次的数字，
		// twice表示对于多次的数字记录，然后删除once中的记录，最后在once中便是出现一次的数字
		unordered_set<int> once, twice;
		for (auto num : nums)
		{
			if (once.count(num))
			{
				twice.count(num);
				once.erase(num);
			}
			else if (twice.count(num))
				continue;
			else
				once.insert(num);
		}
		return *once.begin();
	}
};