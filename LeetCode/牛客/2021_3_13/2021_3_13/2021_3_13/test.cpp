// 用后缀表达式写一个计算器
#include <iostream>
using namespace std;
#include <string>
#include <stack>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>

// 将string类型的转换成int
int f(string s)
{
	stringstream ss;
	ss << s;
	int num;
	ss >> num;
	return num;
}

int main()
{
	int n;
	while (cin >> n)
	{
		stack<int> st;

		for (int i = 0; i < n; ++i)
		{
			string x;
			cin >> x;
			// 用栈来操作，取两个元素，然后进行加减乘除
			if (x == "+")
			{
				int num1 = st.top();
				st.pop();
				int num2 = st.top();
				st.pop();

				num1 += num2;
				st.push(num1);
			}
			else if (x == "-")
			{
				int num1 = st.top();
				st.pop();
				int num2 = st.top();
				st.pop();

				num2 -= num1;
				st.push(num2);
			}
			else if (x == "*")
			{
				int num1 = st.top();
				st.pop();
				int num2 = st.top();
				st.pop();

				num1 *= num2;
				st.push(num1);
			}
			else if (x == "/")
			{
				int num1 = st.top();
				st.pop();
				int num2 = st.top();
				st.pop();

				num2 /= num1;
				st.push(num2);
			}
			else {
				int num = f(x);
				st.push(num);
			}
		}
		cout << st.top() << endl;
	}
	return 0;
}