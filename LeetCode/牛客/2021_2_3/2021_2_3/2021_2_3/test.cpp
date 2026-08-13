// 淘宝网店

#include<iostream>
using namespace std;
static int A[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
static int Arr[13] = { 0, 2, 1, 1, 2, 1, 2, 1, 2, 2, 2, 1, 2 };
int GetMoney(int month)  //获得每月每天的钱数
{
	return Arr[month];
}
int GetDay(int year, int month) //获得每月的天数
{
	if (((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) && month == 2)
		return 29;
	return A[month];
}
int main()
{
	int year1, month1, day1, year2, month2, day2;
	while (cin >> year1 >> month1 >> day1 >> year2 >> month2 >> day2)
	{
		int money = 0;
		if (year1 == year2 && month1 == month2 && day1 == day2)
		{
			money += GetMoney(month1);
		}
		while (year1 != year2 || month1 != month2 || day1 != day2)
		{
			int ret = 0;
			if (year1 == year2 && month1 == month2)
			{
				ret = day2 - day1 + 1;
				money += (GetMoney(month1) * ret);
				break;
			}
			ret = GetDay(year1, month1) - day1 + 1;
			money += ret * GetMoney(month1);
			++month1;
			if (month1 == 13)
			{
				++year1;
				month1 = 1;
			}
			day1 = 1;
		}
		cout << money << endl;
	}
	return 0;
}