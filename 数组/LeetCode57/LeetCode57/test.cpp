class Solution {
public:
	vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
		int left = newInterval[0];
		int right = newInterval[1];
		bool placed = false; // 用placed表示这个要插入的数字只能插入一次
		vector<vector<int>> ans;
		for (const auto interval : intervals){
			if (interval[0] > right){ // 这种是已经过了要插入的地方
				if (!placed){
					ans.push_back({ left, right });
					placed = true; // 需要及时更改
				}
				ans.push_back(interval);
			}
			else if (interval[1] < left){ // 这种是还没到要插入的地方
				ans.push_back(interval);
			}
			else {
				// 这种情况就是交集
				left = min(left, interval[0]);
				right = max(right, interval[1]);
			}
		}
		if (!placed){
			ans.push_back({ left, right });
		}
		return ans;
		// 这种不用考虑怎么更改每个区间的left，right，这种只用可以更新left和right的值，最后没有插入的时候，将其插入进去
	}
};