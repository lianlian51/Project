class Solution {
public:
	string reverseLeftWords(string s, int n) {
		n = n % s.size();
		string str;
		for (int i = 0; i < n; ++i)
		{
			str += s[i];
		}
		s.erase(0, n);
		s += str;
		return s;
	}
};