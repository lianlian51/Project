#include<cstdio>
#include<vector>
#include<cstring>
#include<string>
#include<map>
using namespace std;
int ans, m;
char pre[27], post[27];
map<char, int> postidx;

void Count(int preS, int preE, int postS, int postE);
int mCk(int m, int k);

int main()
{
	while (scanf("%d %s %s", &m, pre, post) != EOF)
	{
		ans = 1;
		for (int i = 0; i<strlen(post); i++)
			postidx[post[i]] = i;
		Count(0, strlen(pre) - 1, 0, strlen(post) - 1);
		printf("%d\n", ans);
	}//while
	return 0;
}//main

void Count(int preS, int preE, int postS, int postE)
{
	if (preS >= preE)
		return;
	int i = preS + 1, cnt = 0;
	int idx = postidx[pre[i]];
	while (i <= preE)
	{
		Count(i, i + idx - postS, postS, idx);
		cnt++;
		if (idx != postE - 1)
		{
			i += idx - postS + 1;   
			postS = idx + 1;  
			idx = postidx[pre[i]];
		}
		else
			break;
	}
	ans *= mCk(m, cnt);
}

int mCk(int m, int k)
{
	int numerator = 1, denominator = 1;
	for (int i = 0; i<k; i++, m--)
		numerator *= m;
	for (int i = 1; i <= k; i++)
		denominator *= i;
	return numerator / denominator;
}



