class Solution {
public:
	bool wordBreak(string s, vector<string>& wordDict) {
		unordered_set<string> word_set;
		for (auto & word : wordDict)
		{
			word_set.insert(word);
		}
		int len = s.size();
		vector<bool> dp(len + 1);
		dp[0] = true;
		for (int i = 1; i <= len; ++i)
		{
			for (int j = 0; j < i; ++j)
			{
				if (dp[j] && word_set.find(s.substr(j, i - j)) != word_set.end())
				{
					dp[i] = true;
					break;
				}
			}
		}
		return dp[len];
	}
};