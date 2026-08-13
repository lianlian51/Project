class Solution {
public:
	int lengthOfLongestSubstring(string s) {
		int map[128] = { 0 };
		int len, start = 0;
		for (int i = 0; i < s.size(); i++)
		{
			map[s[i]]++;
			while (map[s[i]] == 2)
				--map[s[start++]];
			len = max(len, i - start + 1);
		}
		return len;
	}
};