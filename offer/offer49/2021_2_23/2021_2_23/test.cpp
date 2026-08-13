class Solution {
public:
	typedef long long LL;
	const int ugly[3] = { 2, 3, 5 };

	int nthUglyNumber(int n) {
		priority_queue<LL, vector<LL>, greater<LL>> pq;
		set<LL> s;

		pq.push(1);
		s.insert(1);
		for (int i = 1;; i++)
		{
			LL x1 = pq.top();
			pq.pop();

			if (i == n)
				return x1;
			for (int j = 0; j < 3; j++)
			{
				LL x = ugly[j] * x1;
				if (!s.count(x))
				{
					s.insert(x);
					pq.push(x);
				}
			}
		}

	}
};