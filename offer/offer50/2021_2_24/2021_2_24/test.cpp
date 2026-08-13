class Solution {
public:
	char firstUniqChar(string s) {
		int map[128] = { 0 };
		for (int i = 0; i< s.size(); i++)
		{
			map[s[i]]++;
		}
		for (int i = 0; i<s.size(); i++)
		{
			if (map[s[i]] == 1)
				return s[i];
		}
		return ' ';
	}
};