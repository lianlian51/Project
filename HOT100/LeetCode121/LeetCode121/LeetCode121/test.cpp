class Solution {
public:
	int maxProfit(vector<int>& prices) {
		int inf = 1e9;
		int minprices = inf;
		int maxprofit = 0;
		for (int e : prices)
		{
			maxprofit = max(maxprofit, e - minprices);
			minprices = min(minprices, e);
		}
		return maxprofit;
	}
};