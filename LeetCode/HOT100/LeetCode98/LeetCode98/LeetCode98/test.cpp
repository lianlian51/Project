///**
//* Definition for a binary tree node.
//* struct TreeNode {
//*     int val;
//*     TreeNode *left;
//*     TreeNode *right;
//*     TreeNode() : val(0), left(nullptr), right(nullptr) {}
//*     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
//*     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
//* };
//*/
//class Solution {
//public:
//	bool func(TreeNode* root, long long lower, long long upper)
//	{
//		if (root == nullptr){
//			return true;
//		}
//		if (root->val <= lower || root->val >= upper){
//			return false;
//		}
//		return func(root->left, lower, root->val) && func(root->right, root->val, upper);
//	}
//
//	bool isValidBST(TreeNode* root) {
//		return func(root, LONG_MIN, LONG_MAX);
//	}
//};



#include <iostream>
using namespace std;
#include <vector>
#include <algorithm>
#include <limits.h>

int func(vector<int> v, int i, int j)
{
	int ret = 0;
	for (int k = i; k <= j; ++k){
		ret += v[k];
	}
	return ret;
}

int main()
{
	int n;
	while (cin >> n){
		vector<int> v(n);
		for (int i = 0; i < n; ++i){
			cin >> v[i];
		}

		int ret = INT_MIN;
		int left = 0;
		int right = 0;
		for (int i = 0; i < n; ++i){
			for (int j = i + 1; j < n; ++j){
				int tmp = func(v, i, j);
				if (tmp > ret){
					left = i;
					right = j;
				}
			}
		}
		cout << left << "," << right << endl;
	}
	return 0;
}