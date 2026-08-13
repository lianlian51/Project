// 输入一个字符串，打印出该字符串中字符的所有排列。

// 你可以以任意顺序返回这个字符串数组，但里面不能有重复元素。

#include <iostream>
using namespace std;
#include <string>
#include <set>
#include <vector>

void BackTrace(string s, set<string>& res, int start)
{
	if (start == s.size())
	{
		res.insert(s);
		return;
	}
	for (int i = start; i < s.size(); i++)
	{
		// 交换方式
		swap(s[i], s[start]);
		BackTrace(s, res, start + 1);
		swap(s[i], s[start]);
	}
}

vector<string> permutation(string s)
{
	// 去重处理
	set<string> res;
	BackTrace(s, res, 0);
	return vector<string>(res.begin(), res.end());
}

int main()
{
	string s("abc");
	vector<string> v;
	v = permutation(s);
	for (auto & e : v)
		cout << e << endl;
	return 0;
}