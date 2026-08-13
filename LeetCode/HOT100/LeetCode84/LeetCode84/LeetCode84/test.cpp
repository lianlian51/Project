class Solution {
public:
	int largestRectangleArea(vector<int>& heights) {
		int n = heights.size();
		// 保存左右边界的值
		vector<int> left(n), right(n, n);

		stack<int> mono_stack;
		for (int i = 0; i < n; ++i)
		{
			while (!mono_stack.empty() && heights[mono_stack.top()] >= heights[i])
			{
				right[mono_stack.top()] = i;
				mono_stack.pop();
			}
			// 对于是升序的情况，就直接将栈顶作为哨兵
			// 降序的情况直接将i给top（这里的top一定是i的前一个位置），降序需要出栈
			left[i] = mono_stack.empty() ? -1 : mono_stack.top();
			mono_stack.push(i);
		}

		int ans = 0;
		for (int i = 0; i < n; ++i)
		{
			// 算出最大值
			ans = max(ans, (right[i] - left[i] - 1) * heights[i]);
		}
		return ans;
	}
};