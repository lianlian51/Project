
class Solution {
public:
	int findDuplicate(vector<int>& nums) {
		// fisrt :二分法
		/*
		int n = nums.size();
		int l = 1, r = n - 1, ans = -1;
		while(l <= r)
		{
		int mid = (l + r) >> 1;
		int cnt = 0;
		for(int i = 0; i < n; ++i)
		{
		if(nums[i] <= mid)
		cnt++;
		}
		if(cnt <= mid)
		l = mid + 1;
		else {
		r = mid - 1;
		ans = mid;
		}
		}
		return ans;
		*/

		// second : 二进制法
		// 1.获取最大的比特位,这里获取的比特位数是下标
		/*
		int n = nums.size(), ans = 0;
		int bit_max = 31;
		while(!((n - 1) >> bit_max))
		--bit_max;

		for(int bit = 0; bit <= bit_max; ++bit)
		{
		// 1.分别计算出每一位1的个数
		// x记录数组nums中1的个数，y记录[1,n - 1]中1的个数
		int x = 0, y = 0;
		for(int i = 0; i < n; ++i)
		{
		if(nums[i] & (1 << bit))
		++x;
		if(i >= 1 && (i & (1 << bit)))
		++y;
		}
		// x > y说明那个位置的比特位是重复数字的
		if(x > y)
		ans |= (1 << bit);
		}
		return ans;
		*/

		// third : 快慢指针、floyd判圈算法
		// 我们对nums 数组建图，每个位置 i 连一条 i→nums[i] 的边。由于存在的重复的数字 target，因此 target 这个位置一定有起码两条指向它的边，因此整张图一定存在环，且我们要找到的target 就是这个环的入口。
		int slow = 0, fast = 0;
		do
		{
			slow = nums[slow];
			fast = nums[nums[fast]];
		} while (fast != slow);

		slow = 0;
		while (slow != fast)
		{
			slow = nums[slow];
			fast = nums[fast];
		}

		return fast;
	}
};