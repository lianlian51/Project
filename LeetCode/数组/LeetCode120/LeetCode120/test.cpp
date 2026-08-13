#include <iostream>
#include <string>
#include <vector>
using namespace std;
#include <algorithm>

class Solution {
public:
	int minimumTotal(vector<vector<int>>& triangle) {
		vector<int> dp(triangle.back());
		for (int i = triangle.size() - 2; i >= 0; --i){
			for (int j = 0; j <= i; ++j){
				dp[j] = min(dp[j], dp[j + 1]) + triangle[i][j];
			}
		}
		return dp[0];
	}
};


// 方法二
class Solution {
public:
	int minimumTotal(vector<vector<int>>& triangle) {
		// 动态规划
		int n = triangle.size();
		vector<vector<int>> f(n, vector<int>(n));
		f[0][0] = triangle[0][0];
		for (int i = 1; i < n; ++i){
			// 赋值每行第一个元素
			f[i][0] = f[i - 1][0] + triangle[i][0];
			for (int j = 1; j < i; ++j){
				// 赋值每行中间的元素
				f[i][j] = min(f[i - 1][j - 1], f[i - 1][j]) + triangle[i][j];
			}
			// 赋值每行最后一个元素
			f[i][i] = f[i - 1][i - 1] + triangle[i][i];
		}
		// 返回最后一行最小的元素
		return *min_element(f[n - 1].begin(), f[n - 1].end());
	}
};