class Solution {
public:
	void DFS(int n, int left, int right, string& tmp, vector<string>& result)
	{
		if (tmp.size() == n * 2)
		{
			result.push_back(tmp);
			return;
		}
		if (left < n)
		{
			tmp.push_back('(');
			DFS(n, left + 1, right, tmp, result);
			tmp.pop_back();
		}
		// 这里来防止不是有效的括号
		if (right < left)
		{
			tmp.push_back(')');
			DFS(n, left, right + 1, tmp, result);
			tmp.pop_back();
		}
	}

	vector<string> generateParenthesis(int n) {
		vector<string> result;
		string tmp;
		DFS(n, 0, 0, tmp, result);
		return result;
	}
};