// 剑指 Offer 45. 把数组排成最小的数
// 输入一个非负整数数组，把数组里所有数字拼接起来排成一个数，打印能拼接出的所有数字中最小的一个。

class Solution {
public:
	string minNumber(vector<int>& nums) {
		vector<string> strs;  // 这里将原来的数组转换成字符串
		string ret;           // 返回最后的字符串
		for (auto e : nums)
			strs.push_back(to_string(e));

		sort(strs.begin(), strs.end(), cmp);

		for (auto e : strs)
			ret += e;

		return ret;
	}


	// bool来决定是否要排序
	static bool cmp(const string& a, const string& b)
	{
		return a + b < b + a;
	}
};