class Solution {
public:
	vector<int> t;
	vector<vector<int>> res;

	vector<vector<int>> subsets(vector<int>& nums) {
		int len = nums.size();
		// 这里的mask是每次加1，以三个数字为例
		// 000 将空数组填入到res
		// 001,010,100  将一个数字填入数组
		// 011,101,110  将两个数字填入res
		// 111 将三个数字填入res
		for (int mask = 0; mask < (1 << len); ++mask)
		{
			t.clear();
			for (int i = 0; i < len; ++i)
			{
				// 只要按位与存在的话，就将对应的nums[i]放在临时t中，最后完毕之后将数字填入到res中
				if (mask & (1 << i))
				{
					t.push_back(nums[i]);
				}
			}
			res.push_back(t);
		}
		return res;
	}
};