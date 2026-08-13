/**
* Definition for a binary tree node.
* struct TreeNode {
*     int val;
*     TreeNode *left;
*     TreeNode *right;
*     TreeNode() : val(0), left(nullptr), right(nullptr) {}
*     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
*     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
* };
*/
class Solution {
public:
	int Max(TreeNode* root)
	{
		if (root == nullptr)
			return 0;

		int left = Max(root->left);
		int right = Max(root->right);
		return max(left, right) + 1;
	}

	int maxDepth(TreeNode* root) {
		return Max(root);
	}
};