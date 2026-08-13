class Solution {
public:
	int maxArea(vector<int>& height) {
		int l = 0, r = height.size() - 1;
		int result = 0;
		while (l < r)
		{
			int tmp = min(height[l], height[r]) * (r - l);
			result = max(tmp, result);
			if (height[l] <= height[r])
				++l;
			else
				--r;
		}
		return result;
	}
};