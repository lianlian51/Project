class Solution {
public:
	bool Palindrome(string s)
	{
		int i = 0;
		int j = s.size() - 1;
		while (i < j)
		{
			if (s[i] != s[j])
				return false;
			++i, --j;
		}
		if (i >= j)
			return true;
		else
			return false;
	}

	string longestPalindrome(string s) {
		int len = s.size();
		if (len <= 1)
			return s;

		string result = "";
		for (int i = 0; i < len; ++i)
		{
			int j = 1;
			while (i + j <= len)
			{
				string temp = s.substr(i, j);
				if (Palindrome(temp))
				{
					if (temp.size() > result.size())
					{
						result = temp;
					}
				}
				++j;
			}
		}
		return result;
	}
};