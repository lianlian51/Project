
class Solution {
public:
	vector<int> productExceptSelf(vector<int>& nums) {
		int n = nums.size();
		std::vector<int> ret(n, 1);
		// prefix记录左边的积，suffix记录右边的积
		int prefix = 1, suffix = 1;
		for (int i = 0; i < n; ++i)
		{
			ret[i] *= prefix;
			ret[n - i - 1] *= suffix;
			prefix *= nums[i];
			suffix *= nums[n - i - 1];
		}
		return ret;
	}
};