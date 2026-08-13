class Solution {
public:
	// 将数字计算出来
	string getDig(string& s, int& ptr)
	{
		string ret = "";
		while (isdigit(s[ptr]))
		{
			ret += s[ptr++];
		}
		return ret;
	}

	// 将数组中放字符串转化为字符串
	string getString(vector<string> s)
	{
		string ret = "";
		for (auto & e : s)
			ret += e;
		return ret;
	}

	string decodeString(string s) {
		int len = s.size();
		int ptr = 0;
		vector<string> stk;
		while (ptr < len)
		{
			char cur = s[ptr];
			if (isdigit(cur))
			{
				string temp = getDig(s, ptr);
				stk.push_back(temp);
			}
			else if (isalpha(s[ptr]) || s[ptr] == '[')
			{
				stk.push_back(string(1, s[ptr++]));
			}
			else
			{
				++ptr;
				vector<string> temp;
				while (stk.back() != "[")
				{
					temp.push_back(stk.back());
					stk.pop_back();
				}
				reverse(temp.begin(), temp.end());
				// 左括号出栈
				stk.pop_back();
				string t, o = getString(temp);
				int times = stoi(stk.back());
				// 数字出栈
				stk.pop_back();
				// 构造好字符串入栈：这里这样就是为了防止[]套[]的情况
				for (int i = 0; i < times; ++i)
					t += o;
				stk.push_back(t);
			}
		}
		// 最终将栈中的元素都拼接起来返回
		return getString(stk);
	}
};