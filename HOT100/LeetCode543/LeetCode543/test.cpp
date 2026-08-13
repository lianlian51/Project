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
//	int ans;
//	int Height(TreeNode* root)
//	{
//		if (root == nullptr)
//			return 0;
//		int left = Height(root->left);
//		int right = Height(root->right);
//		ans = max(ans, left + right + 1);
//		return max(left, right) + 1;
//	}
//
//	int diameterOfBinaryTree(TreeNode* root) {
//		ans = 1;
//		Height(root);
//		return ans - 1; // 经过最多的节点-1  
//	}
//};


#include <iostream>
using namespace std;

class A
{
public:
	void aa()
	{
		cout << "aa" << endl;
	}
private:
	int a;
};

class B : private A
{
public:
private:
	int b;
};

class C : private B
{
public:
	void CC()
	{
		cout << "CC" << endl;
	}
private:
	int c;
};


int main()
{
	B bb;
	//bb.

	//C cc;
	//cc.
	return 0;
}