#include <iostream>
using namespace std;
#include <vector>
#include <algorithm>

int skill1_135(vector<vector<int>> v)
{
	int i = 0, j = 0;
	int Max = 0;
	int len = v.size();
	int tmp = 0;
	while (i < len && j < len)
	{
		int _i = i, _j = j;
		while (_i < len && _j < len)
		{
			if (v[_i][_j] == 1)
				tmp++;
			++_i, ++_j;
		}
		Max = max(Max, tmp);
		++j;
	}

	i = 0, j = 0;
	while (i < len && j < len)
	{
		int _i = i, _j = j;
		while (_i < len && _j < len)
		{
			if (v[_i][_j] == 1)
				tmp++;
			++_i, ++_j;
		}
		Max = max(Max, tmp);
		++i;
	}
	return Max;
}

int skill1_45(vector<vector<int>> v)
{
	int len = v.size();
	int i = len - 1, j = 0;
	int Max = 0;

	int tmp = 0;
	while (i >= 0 && j < len)
	{
		int _i = i, _j = j;
		while (_i >= 0 && _j < len)
		{
			if (v[_i][_j] == 1)
				tmp++;
			--_i, ++_j;
		}
		Max = max(Max, tmp);
		++j;
	}

	i = v.size() - 1, j = 0;
	while (i >= 0 && j < len)
	{
		int _i = i, _j = j;
		while (_i >= 0 && _j < len)
		{
			if (v[_i][_j] == 1)
				tmp++;
			--_i, ++_j;
		}
		Max = max(Max, tmp);
		--i;
	}
	return Max;
}

int skill1(vector<vector<int>> nums)
{
	int ret = 0;
	int len = nums.size();
	for (int i = 0; i < len; ++i)
	{
		int tmp = 0;
		for (int j = 0; j < len; ++j)
		{
			if (nums[i][j] == 1)
			{
				tmp += 1;
			}
		}
		ret = max(tmp, ret);
	}

	for (int i = 0; i < len; ++i)
	{
		int tmp = 0;
		for (int j = 0; j < len; ++j)
		{
			if (nums[j][i] == 1)
			{
				tmp += 1;
			}
		}
		ret = max(tmp, ret);
	}

	int tmp = skill1_135(nums);
	ret = max(tmp, ret);
	tmp = skill1_45(nums);
	ret = max(tmp, ret);
	return ret;
}

int skill2N(vector<vector<int>> v, int N, int i, int j)
{
	int lu_h = i - N;
	int rd_h = i + N;
	int lu_z = j - N;
	int rd_z = j + N;
	int res = 0;
	for (int m = lu_h; m < rd_h; ++m)
	{
		for (int n = lu_z; n < rd_z; ++n)
		{
			if (v[m][n] == 1)
				res++;
		}
	}
	return res;
}

int skill2(vector<vector<int>> v, int N, int count)
{
	int len = v.size();
	int res = 0;
	for (int i = N; i < len - N; ++i)
	{
		for (int j = N; j < len - N; ++j)
		{
			int tmp = 0;
			tmp = skill2N(v, N, i, j);
			res = max(tmp, res);
		}
	}
	return res;
}


int main()
{
	int N, count;
	while (cin >> N >> count)
	{
		vector<vector<int>> nums(301, vector<int>(301, 0));
		for (int i = 0; i < count; ++i)
		{
			int x, y;
			cin >> x >> y;
			nums[x][y] = 1;
		}
		int result = 0;
		int sk1 = skill1(nums);
		int sk2 = skill2(nums, N, count);
		result = max(sk1, sk2);
		cout << result << endl;
	}
	return 0;
}