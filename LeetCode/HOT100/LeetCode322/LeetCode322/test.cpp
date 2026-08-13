#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#if 0
int coinChange(vector<int>& coins, int amount) {
	std::sort(coins.begin(), coins.end());
	if (amount == 0)
		return 0;
	int count = 0;
	int i = coins.size() - 1;
	while (amount)
	{
		while (amount >= coins[i])
		{
			count++;
			amount -= coins[i];
		}
		if (amount < coins[i])
		{
			--i;
			if (i < 0)
				break;
		}
	}
	if (amount == 0)
		return count;
	else
		return -1;
}
#endif

	int coinChange(vector<int>& coins, int amount) {
		// 当需要把问题转化为子问题时用动态规划
		int Max = amount + 1;
		vector<int> dp(amount + 1, Max);
		dp[0] = 0;
		for (int i = 1; i <= amount; ++i)
		{
			for (int j = 0; j < (int)coins.size(); ++j)
			{
				if (coins[j] <= i)
					dp[i] = min(dp[i], dp[i - coins[j]] + 1);
			}
		}

		return dp[amount] > amount ? -1 : dp[amount];
	}

int main()
{
	vector<int> vec{ 186, 419, 83, 408};
	int amount = 6249;
	std::cout << coinChange(vec, amount);
	return 0;
}