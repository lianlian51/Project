class Solution {
public:
	int minDistance(string word1, string word2) {
		int m = word1.size();
		int n = word2.size();

		// 判断特殊情况
		if (m * n == 0)
			return m + n;

		int nums[m + 1][n + 1];
		// 边界初始化
		for (int i = 0; i < m + 1; i++)
		{
			nums[i][0] = i;
		}
		for (int j = 0; j < n + 1; ++j)
		{
			nums[0][j] = j;
		}

		for (int i = 1; i < m + 1; i++)
		{
			for (int j = 1; j < n + 1; ++j)
			{
				// 分别表示当前数字的上一个位置，左边的位置，左上的位置操作一次的结果
				// 对于左上的位置，表示字符交换的操作，如果本来就顺序的话，就不用交换，否则交换
				// 左边表示word2的插入或删除和上边对word1的插入或删除
				int up = nums[i - 1][j] + 1;
				int left = nums[i][j - 1] + 1;
				int left_up = nums[i - 1][j - 1];

				if (word1[i - 1] != word2[j - 1])
					left_up += 1;
				nums[i][j] = min(left, min(left_up, up));
			}
		}
		return nums[m][n];
	}
};