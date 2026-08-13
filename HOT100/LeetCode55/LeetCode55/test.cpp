class Solution {
public:
	bool canJump(vector<int>& nums) {
		int len = nums.size();
		// rightmost表示右边可以达到的最长长度
		int rightmost = 0;
		for (int i = 0; i < len; ++i)
		{
			// 如果出现i大于rightmost的情况，那么一定返回false
			if (i <= rightmost)
			{
				rightmost = max(rightmost, i + nums[i]);
				if (rightmost >= len - 1)
					return true;
			}
		}
		return false;
	}
};
