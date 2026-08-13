class Solution {
public:
	string reverseWords(string s) {
		stack<string> stk;
		string str, res;
		istringstream ss(s);
		while (ss >> str)
		{
			stk.push(str);
			stk.push(" ");
		}
		if (!stk.empty())
			stk.pop();

		while (!stk.empty())
		{
			res += stk.top();
			stk.pop();
		}
		return res;
	}
};