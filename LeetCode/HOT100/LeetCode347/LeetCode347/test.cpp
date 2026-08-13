#include <iostream>
using namespace std;
#include <vector>
#include <queue>
#include <unordered_map>
#include <map>

//
//vector<int> topKFrequent(vector<int>& nums, int k) {
//	priority_queue<pair<int, int>, vector<pair<int, int>, less<int>>> pq;
//	for (int i = 0; i < nums.size(); ++i)
//	{
//		pq.push(make_pair(nums[i], nums[i]++));
//	}
//	int len = pq.size();
//	cout << len << endl;
//	for (int i = len; i > k; --i)
//		pq.pop();
//	vector<int> ret;
//	for (int i = 0; i < (int)pq.size(); ++i)
//	{
//		ret.push_back(pq.top());
//		cout << pq.top() << endl;
//		pq.pop();
//	}
//	return ret;
//}
//
//int main()
//{
//	vector<int> num{ 1, 1, 1, 2, 2, 3 };
//	topKFrequent(num, 2);
//	return 0;
//}

class Solution {
public:
	vector<int> topKFrequent(vector<int>& nums, int k) {
		// 利用unordered_map计算出数字的个数
		unordered_map<int, int> m;
		for (auto e : nums)
		{
			m[e]++;
		}

		// 对m中的数字排序，保证降序排序
		multimap<int, int, greater<int>> mm;
		for (auto e : m)
		{
			mm.insert(make_pair(e.second, e.first));
		}
		// 将mm中已排序的数字返回最大的k个
		vector<int> ret;
		for (auto e : mm)
		{
			if (k == 0)
				break;
			ret.push_back(e.second);
			k--;
		}
		return ret;
	}
};