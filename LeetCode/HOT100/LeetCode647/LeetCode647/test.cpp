#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

	int countSubstrings(string s) {
		// manacher算法
		int n = s.size();
		// mach存储加了#的字符串，maxR保存以每个下标为中心的最长匹配半径
		string mach = "$#";
		
		for (const char& c : s)
		{
			mach += c;
			mach += '#';
		}
		n = mach.size();
		mach += '!';
		cout << n << endl;
		auto maxR = vector<int>(n);
		int R = 0, C = 0;
		int ans = 0;
		for (int i = 1; i < n; ++i)
		{
			// 第一步计算最短的回文半径
			maxR[i] = (i <= R) ? min(R - i + 1, maxR[2 * C - i]) : 1;
			// 暴力求解
			while (mach[i + maxR[i]] == mach[i - maxR[i]])
			{
				++maxR[i];
			}
			// 更新R，C
			if (i + maxR[i] - 1 > R)
			{
				R = i + maxR[i] - 1;
				C = i;
			}
			ans += (maxR[i] / 2);
		}
		return ans;
	}


	int main()
	{
		cout << countSubstrings("abc") << endl;
		return 0;
	}