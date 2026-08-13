#if 0
// write your code here cpp
#include <iostream>
#include <vector>
using namespace std;

int main()
{
	int a;
	while (cin >> a)
	{
		vector<int> v;
		int temp = a;
		for (int i = 2; i < temp && a != 1; i++)
		{
			if (a % i == 0)
			{
				while (a % i == 0)
				{
					v.push_back(i);
					a /= i;
				}
			}
		}
		cout << temp << " = ";
		for (int i = 0; i < v.size() - 1; i++)
		{
			cout << v[i] << " * ";
		}
		cout << v[v.size() - 1] << endl;
	}
	return 0;
}
#endif


#include<stdio.h>
#include<math.h>
int main()
{
	int n;
	while (scanf("%d", &n) != EOF)
	{
		printf("%d =", n);
		int i;
		for (i = 2; i <= sqrt(n); i++)
		{
			while (n != i)
			{
				if (n%i == 0)
				{
					printf(" %d *", i);
					n /= i;
				}
				else
					break;				//否则就陷入死循环了 
			}
		}
		printf(" %d\n", n);
	}
	return 0;
}