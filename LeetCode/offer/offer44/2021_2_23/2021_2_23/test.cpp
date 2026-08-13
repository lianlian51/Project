class Solution {
public:
	int findNthDigit(int n) {
		if (n == 0)
			return 0;
		int digit = 1; // 数位
		long start = 1; // 属于该数位的所有数的起始点数
		long index_count = digit * 9 * start; // 该数位中的一共有多少个索引个数
		while (n > index_count)
		{
			n -= index_count;
			++digit;
			start *= 10;
			index_count = digit * 9 * start;
		}

		long num = start + (n - 1) / digit; // 算出原始的n到底对应那个数字
		int remainder = (n - 1) % digit; // 余数就是原始的n是这个数字中的第几位
		string s_num = to_string(num);
		return int(s_num[remainder] - '0');
	}
};