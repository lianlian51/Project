class Solution {
public:
	vector<vector<int>> merge(vector<vector<int>>& intervals) {
		int len = intervals.size();
		if (len <= 1)
			return intervals;
		sort(intervals.begin(), intervals.end());
		vector<vector<int>> res;
		for (int i = 0; i < len;)
		{
			int j = i + 1;
			int tmp = intervals[i][1];
			while (j < len && intervals[j][0] <= tmp)
			{
				tmp = max(intervals[j][1], tmp);
				j++;
			}
			res.push_back({ intervals[i][0], tmp });
			i = j;
		}
		return res;
	}
};