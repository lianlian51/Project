class Solution {
public:
	int maxProduct(vector<int>& nums) {
		int len = nums.size();
		int maxF = nums[0], minF = nums[0], ans = nums[0];
		for (int i = 1; i < len; ++i){
			int mx = maxF, mn = minF;
			maxF = max(mx * nums[i], max(nums[i], mn * nums[i]));
			minF = min(mn * nums[i], min(nums[i], mx * nums[i]));
			ans = max(ans, maxF);
		}
		return ans;
	}
};