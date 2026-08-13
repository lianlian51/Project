#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
using namespace std;


void backtrace(string& s, int leftremove, int rightremove, string& path, unordered_set<string>& temp, int leftcount, int rightcount, int index);
vector<string> removeInvalidParentheses(string s) {
	int n = s.size();
	int leftremove = 0, rightremove = 0;
	// 统计左右括号的数量，这里的统计左右括号的差值abs(left-right)
	for (int i = 0; i < n; ++i)
	{
		if (s[i] == '(')
			++leftremove;
		else if (s[i] == ')')
		{
			if (leftremove == 0)
				++rightremove;
			else if (leftremove > 0)
				--leftremove;
		}
	}
	unordered_set<string> temp;
	string path;
	backtrace(s, leftremove, rightremove, path, temp, 0, 0, 0);
	vector<string> ret(temp.begin(), temp.end());
	return ret;
}

// path记录每次的结果，path中的leftcount记录左括号的数量，path中的rightcount记录右括号的数量，index遍历字符串s
void backtrace(string& s, int leftremove, int rightremove, string& path, unordered_set<string>& temp, int leftcount, int rightcount, int index)
{
	if (index == s.size())
	{
		if (leftremove == 0 && rightremove == 0)
			temp.insert(path);
		return;
	}

	// 删除多于的左括号
	if (s[index] == '(' && leftremove > 0)
	{
		backtrace(s, leftremove - 1, rightremove, path, temp, leftcount, rightcount, index + 1);
	}
	// 删除多于的右括号
	if (s[index] == ')' && rightremove > 0)
	{
		backtrace(s, leftremove, rightremove - 1, path, temp, leftcount, rightcount, index + 1);
	}

	path.push_back(s[index]);
	if (s[index] != '(' && s[index] != ')')
	{
		backtrace(s, leftremove, rightremove, path, temp, leftremove, rightremove, index + 1);
	}
	else if (s[index] == '(')
	{
		backtrace(s, leftremove, rightremove, path, temp, leftcount + 1, rightcount, index + 1);
	}
	else if (rightcount < leftcount)
	{
		backtrace(s, leftremove, rightremove, path, temp, leftcount, rightcount + 1, index + 1);
	}
	path.pop_back();
}


int main()
{
	string s = "(a)())()";
	removeInvalidParentheses(s);
	return 0;
}