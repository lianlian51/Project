class Solution {
public:
	int OneCount(int i)
	{
		int one = 0;
		while (i > 0)
		{
			i &= (i - 1);
			one++;
		}
		return one;
	}

	vector<int> countBits(int n) {
#if 0
		vector<int> ret(n + 1);
		for (int i = 1; i <= n; ++i)
		{
			ret[i] = OneCount(i);
		}
		return ret;
#endif

		vector<int> ret(n + 1);
		int highBit = 0;
		for (int i = 1; i <= n; ++i)
		{
			if ((i & i - 1) == 0)
			{
				highBit = i;
			}
			ret[i] = ret[i - highBit] + 1;
		}
		return ret;
	}
};