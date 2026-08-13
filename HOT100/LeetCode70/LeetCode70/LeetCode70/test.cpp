class Solution {
public:
	int climbStairs(int n) {
		int q = 0, p = 0, r = 1;
		for (int i = 1; i <= n; ++i)
		{
			q = p;
			p = r;
			r = p + q;
		}
		return r;
	}
};