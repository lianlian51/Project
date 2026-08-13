class Solution {
public:
	int lengthOfLongestSubstring(string s) {
		// 保存已有的字符，查找是否重复
		unordered_set<char> s_set;
		int len = s.size();

		int rk = -1;
		int ans = 0;
		for (int i = 0; i < len; ++i)
		{
			// 往后移动的时候，要将s_set中该位置的字符去除
			if (i != 0)
			{
				s_set.erase(s[i - 1]);
			}
			// 如果该位置字符不存在s_set中，则继续往后寻找
			while (rk + 1 < len && !s_set.count(s[rk + 1]))
			{
				s_set.insert(s[rk + 1]);
				++rk;
			}
			// 更新ans
			ans = max(ans, rk - i + 1);
		}
		return ans;
	}
};