class Solution {
public:
	int longestValidParentheses(string s) {
		if (s.empty())
			return 0;

		int maxLen = 0;
		stack<int> st;  // 栈中放（的下标
		st.push(-1);   // 垫一个数字
		for (int i = 0; i < s.size(); ++i)
		{
			if (s[i] == '(')
			{
				st.push(i);
			}
			else
			{
				// 对于是）的情况，就出栈，然后判断如果栈空就压栈，不空的话就修改maxLen的值
				st.pop();
				if (st.empty())
					st.push(i);
				else
					maxLen = max(maxLen, i - st.top());  // （-1，0，1，2）说明这输入连续的三个左括号，然后遇到一个右括号下标3，就出栈一个，（-1，0，1），下一个右括号下标就是4，maxLen修改为2，循环至栈空，算出结果
			}
		}
		return maxLen;
	}
};