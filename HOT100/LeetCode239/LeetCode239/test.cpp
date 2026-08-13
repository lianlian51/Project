//class Solution {
//public:
//	vector<int> maxSlidingWindow(vector<int>& nums, int k) {
//		int n = nums.size();
//		std::vector<int> ret;
//		priority_queue<std::pair<int, int>> q;
//		for (int i = 0; i < k; ++i)
//		{
//			q.emplace(nums[i], i);
//		}
//
//		ret.push_back(q.top().first);
//		for (int i = k; i < n; ++i)
//		{
//			q.emplace(nums[i], i);
//			// 因为每次i++的缘故，所以这里判断小于等于i-k将被剔除
//			while (!q.empty() && q.top().second <= i - k)
//				q.pop();
//
//			ret.push_back(q.top().first);
//		}
//		return ret;
//	}
//};

#include <iostream>
#include <unordered_set>

int main()
{
	int arr[] = { 1, 2, 1, 2, 3 };
	std::unordered_multiset<int> s;
	for (auto e : arr)
		s.insert(e);
	for (auto e : s)
		std::cout << e << " ";

	return 0;
}