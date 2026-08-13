//class Solution {
//public:
//	int removeDuplicates(vector<int>& nums) {
//		int n = nums.size();
//		if (n <= 2){
//			return n;
//		}
//
//		int slow = 2, fast = 2;
//		while (fast < n)
//		{
//			if (nums[slow - 2] != nums[fast]){
//				nums[slow] = nums[fast];
//				++slow;
//			}
//			++fast;
//		}
//		return slow;
//	}
//};

//#include <iostream>
//using namespace std;
//#include <string>
//#include <vector>
//
//int main()
//{
//	string s;
//	while (getline(cin, s))
//	{
//		vector<int> nums;
//		for (int i = 0; i < s.size(); ++i)
//		{
//			if (s[i] >= '0' && s[i] <= '9'){
//				int temp = 0;
//				while (s[i] >= '0' && s[i] <= '9'){
//					temp = temp * 10 + (s[i] - '0');
//					++i;
//				}
//				nums.push_back(temp);
//			}
//		}
//		int n1, n2;
//		int n = nums.size();
//		bool f = true;
//		for (int i = 0; i < n - 1; ++i){
//			if (nums[i] > nums[i + 1] && f){
//				n1 = i + 1;
//				f = false;
//				continue;
//			}
//			if (nums[i] > nums[i + 1] && !f){
//				n2 = i + 2;
//				break;
//			}
//		}
//		std::cout << n1 << " " << n2 << std::endl;
//	}
//	return 0;
//}
//

#include <iostream>
using namespace std;
#include <string>
#include <vector>

int main()
{
	string s;
	while (getline(cin, s))
	{
		int N, X, K;
		bool n = true, x = false, k = false;
		int ns = s.size();
		for (int i = 0; i < ns; ++i){
			if (s[i] >= '0' && s[i] <= '9' && n){
				int temp = 0;
				while (s[i] >= '0' && s[i] <= '9'){
					temp = 10 * temp + (s[i] - '0');
					++i;
				}
				N = temp;
				n = false;
				x = true;
				continue;
			}
			if (s[i] >= '0' && s[i] <= '9' && x){
				int temp = 0;
				while (s[i] >= '0' && s[i] <= '9'){
					temp = 10 * temp + (s[i] - '0');
					++i;
				}
				X = temp;
				x = false;
				k = true;
				continue;
			}
			if (s[i] >= '0' && s[i] <= '9' && k){
				int temp = 0;
				while (s[i] >= '0' && s[i] <= '9'){
					temp = 10 * temp + (s[i] - '0');
					++i;
				}
				K = temp;
				k = false;
				continue;
			}
		}
		vector<int> nums(N, 0);
		nums[X - 1] = 1;
		for (int i = 0; i < K; ++i){
			int n1, n2;
			cin >> n1 >> n2;
			swap(nums[n1 - 1], nums[n2 - 1]);
		}
		int ret = 0;
		for (int i = 0; i < N; ++i){
			if (nums[i] == 1){
				ret = i + 1;
				break;
			}
		}
		cout << ret << endl;
	}
	return 0;
}