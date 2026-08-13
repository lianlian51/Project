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
	void reverse(TreeNode* root)
	{
		if (root == nullptr)
			return;

		TreeNode* left = root->left;
		TreeNode* right = root->right;
		root->left = right;
		root->right = left;
		reverse(root->left);
		reverse(root->right);
	}

	TreeNode* invertTree(TreeNode* root) {
		if (root == nullptr)
			return nullptr;
		reverse(root);
		return root;
	}
};