class Solution {
public:
	bool isMatch(string s, string p) {
		if (s.empty())
		{
			if (p.size() & 1) return false;
			int odd = 1;
			while (odd < p.size())
			{
				if (p[odd] != '*') return false;
				odd += 2;
			}
			return true;
		}
		if (p.length() == 0) return false;

		char cs = s[0], cp = p[0], cpNext = '\0';
		if (p.length() > 1) cpNext = p[1];
		if (cpNext != '*')
		{
			if (cs == cp || cp == '.')
				return isMatch(s.substr(1), p.substr(1));
			else
				return false;
		}
		else
		{
			if (cs == cp || cp == '.')
				return isMatch(s.substr(1), p) || isMatch(s, p.substr(2));
			else
				return isMatch(s, p.substr(2));
		}
	}
};