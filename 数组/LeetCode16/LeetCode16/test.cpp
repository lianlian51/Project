class Solution {
public:
	int threeSumClosest(vector<int>& nums, int target) {
		// 排序+双指针
		sort(nums.begin(), nums.end());

		int n = nums.size();
		int best = 1e7;
		// 采用lambda表达式更新最接近的数字
		auto update = [&](int cur){
			if (abs(cur - target) < abs(best - target))
			{
				best = cur;
			}
		};

		for (int i = 0; i < n; ++i)
		{
			// 此时是在枚举，保证这次和下次的不一样
			if (i > 0 && nums[i] == nums[i - 1]){
				continue;
			}
			int j = i + 1;
			int k = n - 1;
			// 双指针遍历找到最合适的数字
			while (j < k)
			{
				int sum = nums[i] + nums[j] + nums[k];
				// 如果是target，那么就是最接近的数字
				if (sum == target){
					return sum;
				}
				update(sum);
				if (sum > target)
				{
					int k0 = k - 1;
					// 处理相同的数字，和下面的一样，注意处理时防止越界
					while (j < k0 && nums[k0] == nums[k])
						--k0;

					k = k0;
				}
				else {
					int j0 = j + 1;
					while (j0 < k && nums[j0] == nums[j]){
						++j0;
					}
					j = j0;
				}
			}
		}
		return best;
	}
};