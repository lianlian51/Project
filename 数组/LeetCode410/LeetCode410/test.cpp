//class Solution {
//public:
//	int splitArray(vector<int>& nums, int m) {
//		// 动态规划
//		int n = nums.size();
//		vector<vector<long long>> f(n + 1, vector<long long>(m + 1, LLONG_MAX));
//		vector<long long> sub(n + 1, 0);
//		for (int i = 0; i < n; ++i){
//			sub[i + 1] = sub[i] + nums[i];
//		}
//		f[0][0] = 0;
//		for (int i = 1; i <= n; ++i){
//			for (int j = 1; j <= min(i, m); ++j){
//				for (int k = 0; k < i; ++k){
//					f[i][j] = min(f[i][j], max(f[k][j - 1], sub[i] - sub[k]));
//				}
//			}
//		}
//		return (int)f[n][m];
//	}
//};


//#include <iostream>
//using namespace std;
//#include <string>
//#include <vector>
//#include <algorithm>
//
//int main()
//{
//	string s;
//	getline(cin, s);
//	vector<int> nums;
//	for (int i = 0; i < s.size(); ++i){
//		if (s[i] == ' '){
//			continue;
//		}
//		bool flag = false;
//		if (s[i] == '-'){
//			flag = true;
//			++i;
//		}
//
//		int temp = 0;
//		while (s[i] >= '0' && s[i] <= '9'){
//			temp = temp * 10 + (s[i] - '0');
//			++i;
//		}
//		if (flag){
//			temp = -temp;
//		}
//		nums.push_back(temp);
//	}
//	// 枚举+双指针
//	sort(nums.begin(), nums.end());
//	int n = nums.size();
//	vector<vector<int>> res;
//	for (int i = 0; i < n; ++i){
//		if (i > 0 && nums[i] == nums[i - 1]){
//			continue;
//		}
//		vector<int> temp;
//		int l = i + 1;
//		int r = n - 1;
//		int sum = 0;
//		while (l < r){
//			sum = nums[i] + nums[l] + nums[r];
//			if (sum == 0){
//				temp.push_back(nums[i]);
//				temp.push_back(nums[l]);
//				temp.push_back(nums[r]);
//				res.push_back(temp);
//				temp.clear();
//				++l;
//			}
//			else if (sum > 0){
//				r--;
//			}
//			else if (sum < 0){
//				l++;
//			}
//		}
//		if (temp.size() != 0 && temp.size() % 3 == 0){
//			res.push_back(temp);
//		}
//	}
//	for (int i = 0; i < res.size(); ++i){
//		for (int j = 0; j < res[0].size(); ++j){
//			std::cout << res[i][j] << " ";
//		}
//		std::cout << std::endl;
//	}
//
//	return 0;
//}

#include <iostream>
using namespace std;
#include <string>
#include <vector>

int main()
{
	string s;
	getline(cin, s);
	string s1, s2;
	int p1 = 0, p2 = 0;
	bool flag = false;
	for (int i = 0; i < s.size(); ++i){
		if (s[i] = ' '){
			flag = true;
		}
		else if (!flag){
			if (s[i] == '.'){
				++p1;
			}
			else if (s[i] >= '0' && s[i] <= '9'){
				s1 += s[i];
			}
		}
		else if (flag){
			if (s[i] == '.'){
				++p2;
			}
			else if (s[i] >= '0' && s[i] <= '9'){
				s2 += s[i];
			}
		}
	}
	int res = 0;
	if (p1 == p2){
		int p = 0;
		int i = 0, j = 0;
		int n1 = s1.size(), n2 = s2.size();
		while (p < p1){
			int num1 = 0, num2 = 0;
			while (s1[i] == '0'){ // 处理前导0
				++i;
			}
			while (i < n1 && s1[i] != '.'){
				num1 = num1 * 10 + (s1[i] - '0');
			}
			while (s2[j] == '0'){
				++j;
			}
			while (j < n2 && s2[j] != '.'){
				num2 = num2 * 10 + (s2[j] - '0');
			}
			if (s1[i] == '.' && s2[j] == '.'){
				++i, ++j;
				++p;
			}
			if (num1 > num2){
				res = 1;
				break;
			}
			else if (num2 < num2){
				res = -1;
				break;
			}
		}
	}
	if (p1 == p2){
		std::cout << res << std::endl;
	}
	else {
		if (p1 > p2){
			std::cout << 1 << std::endl;
		}
		else if (p1 < p2){
			std::cout << -1 << std::endl;
		}
	}
	return 0;
}