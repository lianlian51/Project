// 排序算法
class Solution {
public:
	int findRepeatNumber(vector<int>& nums) {
		// 先对数组进行排序
		sort(nums.begin(), nums.end());

		// 然后找相邻的数字是否相同，相同即返回，
		// 循环至结束，没有找到的话就返回-1
		for (int i = 0; i < nums.size(); ++i)
		{
			int j = i + 1;
			if (nums[i] == nums[j])
				return nums[i];
		}
		return -1;
	}
};


// 标记法
class Solution {
public:
	int findRepeatNumber(vector<int>& nums) {
		//创建一个char数组
		unsigned char tmp[nums.size()];
		// 将数组的所有字符全部设置为0（这里的0字符常量，四个字节）
		memset(tmp, 0, nums.size());
		for (int i = 0; i < nums.size(); ++i)
		{
			// 如果这里tmp[nums[i]]是1，不是第一次出现，就返回
			if (tmp[nums[i]])
				return nums[i];
			// 是第一次出现则置为1
			tmp[nums[i]] = 1;
		}
		return -1;
	}
};
