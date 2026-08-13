class Solution {
public:
	vector<int> singleNumbers(vector<int>& nums) {
		int n = 0;
		// n是x^y的值
		for (auto num : nums)
			n ^= num;
		// 循环左移，计算m
		int m = 1;
		while ((n & m) == 0)
			m <<= 1;
		// 拆分数组
		int x = 0, y = 0;
		for (auto num : nums)
		{
			if (num & m)
				x ^= num;
			else
				y ^= num;
		}
		return vector<int> {x, y}; // 返回出现一次的数字
	}
};