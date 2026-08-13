

// 收件人列表

#include <iostream>
using namespace std;
#include <string>

int main()
{
	int n;
	while (cin >> n)
	{
		getchar(); //刷新缓冲区
		while (n--)
		{
			string str;
			getline(cin, str);
			if (str.find(',') != -1 || str.find(' ') != -1)
			{
				str.insert(str.begin(), '"');
				str.insert(str.end(), '"');
			}
			if (n == 0)
				cout << str << endl;
			else
				cout << str << ", ";
		}
	}
	return 0;
}