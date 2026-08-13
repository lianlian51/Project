////#include <iostream>
////#include <string>
////
////class A
////{
////public:
////	std::string s()const{
////		return *_s;
////	}
////
////	A(A& a)
////		: _s(a.s())
////	{}
////	// 拷贝构造
////	A operator()(const std::string& a)
////	{
////		if (this != &a)
////		{
////			_s = a._s;
////		}
////		return *this;
////	}
////	// 赋值运算符重载
////	A& operator=(const A& a)
////	{
////		if (this != &a)
////		{
////			_s = a._s;
////		}
////		return *this;
////	}
////private:
////	std::string *_s;
////};
////
////int main()
////{
////	std::string input;
////	std::cin >> input;
////	A a(input);
////	A b(a);
////	std::cout << b.s() << std::endl;
////	A c;
////	c = b;
////	std::cout << c.s() << std::endl;
////	return 0;
////}
//
//#include <vector>
//#include <string>
//#include <iostream>
//using namespace std;
//
//string find(vector<string>& data_vec) {
//	int l = data_vec.size();
//	vector<vector<char>> vv(l);
//	int lmin = INT_MAX;
//	for (int i = 0; i < l; ++i){
//		string s = data_vec[i];
//		int li = s.size();
//		vv[i].resize(li);
//		if (lmin > li)
//			lmin = li;
//		for (int j = 0; j < li; ++j){
//			vv[i][j] = s[j];
//		}
//	}
//	string ret;
//	int i, j;
//	for (i = 0; i < lmin; ++i)
//	{
//		for (j = 0; j < l - 1; ++j)
//		{
//			if (vv[j][i] != vv[j + 1][i])
//				break;
//		}
//		if (j != l - 1)
//			break;
//		ret += vv[i][i];
//	}
//	return ret;
//}
//
//int main()
//{
//	vector<string> data{ "abcdedfel", "abcdljoieoa", "abcdjlejoa", "abcdwsew" };
//	cout << find(data) << endl;
//	return 0;
//}
//
//
////#include <iostream>
////#include <string>
////using namespace std;
////
////int main()
////{
////	string s = "abcdef";
////	char ch = s[0];
////	cout << ch << endl;
////	return 0;
////}






















//
//#include <iostream>
//using namespace std;
//#include <vector>
//
//int main()
//{
//	int T;
//	cin >> T;
//	while (--T)
//	{
//		int n, m;
//		cin >> n >> m;
//		vector<int> vn(n), vm(m);
//		for (int i = 0; i < n; ++i){
//			cin >> vn[i];
//		}
//
//		for (int i = 0; i < m; ++i){
//			cin >> vm[i];
//		}
//
//		vector<int> ret(n);
//		for (int i = 0; i < n; ++i){
//			int count = 0;
//			int tmp = vn[i];
//			for (int j = 0; j < m; ++j){
//				if (tmp <= vm[j]){
//					count++;
//				}
//			}
//			ret[i] = count;
//		}
//		for (int i = 0; i < n; ++i){
//			cout << ret[i] << " ";
//		}
//		cout << endl;
//	}
//	return 0;
//}

#include <iostream>
using namespace std;
#include <vector>

int main()
{
	int n, m;
	while (cin >> n >> m)
	{
		vector<char> str;
		vector<vector<int>> vv(n, vector<int>(2));
		for (int i = 0; i < n; ++i){
			scanf("%s",&str[i]);
			cin >> vv[i][0] >> vv[i][1];
			vv[i][0]--, vv[i][1]--;
		}

		vector<vector<int>> nums(n, vector<int>(1));
		for (int i = 0; i < n; ++i){
			nums[i][0] = i;
		}

		vector<int> ret;
		for (int i = 0; i < n; ++i){
			vector<int> close;
			if (str[i] == 'C'){
				close.push_back(vv[i][0]);
				int l = nums[i].size();
				for (int j = 0; j < l; ++j){
					nums[vv[i][1]].push_back(vv[i][j]);
				}
			}
			else if (str[i] == 'Q')
			{
				int fi = vv[i][0], se = vv[i][1];
				for (int j = 0; j < n; ++i){
					int ll = close.size();
					for (int k = 0; k < ll; ++k){
						if (j == close[k])
							continue;
					}
					int left = -1, right = -1;
					int l = nums[j].size();
					for (int k = 0; k < l; ++k){
						if (nums[j][k] == fi){
							left = k;
						}
						if (nums[j][k] == se){
							right = k;
						}
					}
					if (left != -1 && right != -1){
						right -= (left + 1);
						ret.push_back(right);
					}
					else {
						ret.push_back(-1);
					}
				}
			}
		}
		int l = ret.size();
		for (int i = 0; i < l; ++i){
			cout << ret[i] << endl;
		}
	}
	return 0;
}