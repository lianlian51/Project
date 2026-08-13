////#include <iostream>
////using namespace std;
////#include <vector>
////#include <string>
////#include <stdlib.h>
////
////int main()
////{
////	string s;
////	while (cin >> s){
////		vector<int> nums;
////		int len = s.size();
////		for (int i = 0; i < len; ++i){
////			if (s[i] >= '0' && s[i] <= '9'){
////				if (s[i + 1] >= '0' && s[i + 1] <= '9'){
////					int a = s[i] - '0';
////					int b = s[i + 1] - '0';
////					nums.push_back(a*10+b);
////					++i;
////				}
////				else
////					nums.push_back(s[i] - '0');
////			}
////		}
////
////		len = nums.size();
////		vector<int> v(32, 0);
////		for (int i = 0; i < len; ++i){
////			int tmp = nums[i];
////			v[tmp] = 1;
////		}
////		for (int i = 0; i < len; i += 2){
////			for (int j = nums[i]; j < nums[i + 1]; ++j){
////				v[j] = 1;
////			}
////		}
////		vector<int> ret;
////		for (int i = 0; i < 32; ++i){
////			if (v[i] != 1){
////				continue;
////			}
////			int left = i;
////			int right = i + 1;
////			while (right < 32 && v[right] == 1){
////				right++;
////			}
////			ret.push_back(left);
////			ret.push_back(right - 1);
////			i = right;
////		}
////		int i;
////		int l = ret.size() - 2;
////		for (i = 0; i < l; i += 2){
////			cout << ret[i] << "-" << ret[i + 1] << ",";
////		}
////		cout << ret[i] << "-" << ret[i + 1] << endl;
////	}
////	return 0;
////}
//
//
//#include <iostream>
//using namespace std;
//#include <vector>
//#include <algorithm>
//
//int main()
//{
//	int tmp;
//	while (cin >> tmp){
//		vector<int> nums;
//		nums.push_back(tmp);
//		while (cin >> tmp){
//			nums.push_back(tmp);
//		}
//
//		int k;
//		cin >> k;
//
//		vector<int> ret;
//		int l = nums.size();
//		if (l < k){
//			sort(ret.begin(), ret.end());
//			cout << "[" << ret[l - 1] << "]" << endl;
//			goto end;
//		}
//		for (int i = 0; i < l; ++i){
//			vector<int> temp(nums[i], k * sizeof(int));
//			sort(temp.begin(), temp.end());
//			int Max = temp[k + i - 1];
//			ret.push_back(Max);
//		}
//		l = ret.size();
//		cout << "[";
//		int i;
//		for (i = 0; i < l - 1; ++i){
//			cout << ret[i] << ",";
//		}
//		cout << ret[i] << "]" << endl;
//	end:;
//	}
//	return 0;
//}
//


#include <iostream>
using namespace std;
#include <vector>

void func(vector<int>& v, int i, int j)
{
	int newi = i, newj = j;
	while (newi < newj)
	{
		swap(v[newi], v[newj]);
		++newi, --newj;
	}
}

int main()
{
	int n, k;
	while (cin >> n >> k)
	{
		vector<int> v(n);
		for (int i = 0; i < n; ++i){
			v[i] = i + 1;
		}
		vector<pair<int, int>> nums(k);
		for (int i = 0; i < k; ++i){
			cin >> nums[i].first >> nums[i].second;

		}

		for (int i = 0; i < k; ++i){
			func(v, nums[i].first - 1, nums[i].second - 1);
		}

		for (int i = 0; i < n; ++i){
			cout << v[i] << " ";
		}
		cout << endl;
	}
	return 0;
}