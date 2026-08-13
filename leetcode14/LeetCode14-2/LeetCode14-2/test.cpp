class Solution {
public:
	string longestCommonPrefix(vector<string>& strs) {
#if 0
		// 排序
		if (strs.empty()) return string();
		sort(strs.begin(), strs.end());
		string st = strs.front(), en = strs.back();
		int i, num = min(st.size(), en.size());
		for (i = 0; i < num && st[i] == en[i]; ++i);
		return string(st, 0, i);
#endif 
#if 0
		// 横向扫描
		if (strs.empty()) return string();
		string ret = strs[0];
		for (int i = 1; i < strs.size(); ++i)
		{
			ret = longString(ret, strs[i]);
			if (!ret.size())
			{
				break;
			}
		}
		return ret;
	}

	string longString(string str1, string str2)
	{
		int index = 0;
		int size = min(str1.size(), str2.size());
		// 越界问题
		while (index < size && str1[index] == str2[index])
		{
			index++;
		}
		return str1.substr(0, index);
#endif
		// 纵向扫描
		if (strs.empty()) return string();
		int size = strs[0].size();
		int count = strs.size();
#if 0
		for (int i = 0; i < size; ++i)
		{
			char c = strs[0][i];
			for (int j = 1; j < count; ++j)
			{
				if (i == strs[j].size() || strs[j][i] != c)
					return string(strs[0], 0, i);
			}
		}
#endif
		return strs[0];
	}
};