class Solution {
public:
	int minSubArrayLen(int target, vector<int>& nums) {
		int n = nums.size();
		if (n <= 0){
			return 0;
		}
		int start = 0, end = 0;
		int ans = INT_MAX;
		int sum = 0;
		while (end < n){
			sum += nums[end];
			while (sum >= target){
				ans = min(ans, end - start + 1);
				sum -= nums[start];
				++start;
			}
			++end;
		}
		return ans == INT_MAX ? 0 : ans;
	}
};




class Solution {
public:
	int minSubArrayLen(int target, vector<int>& nums) {
		// 前缀和+二分查找
		int ans = INT_MAX;
		int n = nums.size();
		if (n == 0){
			return 0;
		}
		vector<int> sums(n + 1, 0);
		for (int i = 1; i <= n; ++i){
			sums[i] = sums[i - 1] + nums[i - 1];
		}
		for (int i = 1; i <= n; ++i){
			int s = target + sums[i - 1];
			auto bound = lower_bound(sums.begin(), sums.end(), s);
			if (bound != sums.end()){
				ans = min(ans, static_cast<int>(bound - sums.begin() - (i - 1)));
			}
		}
		return ans == INT_MAX ? 0 : ans;
	}
};