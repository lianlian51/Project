class Solution {
public:
	int mySqrt(int x) {
		int l = 0, r = x;
		int ans;
		while (l <= r){
			int m = (l + r) / 2;
			if ((long long)m * m <= x){
				ans = m;
				l = m + 1;
			}
			else{
				r = m - 1;
			}
		}
		return ans;
	}
};