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
	unordered_map<int, int> index;
	TreeNode* mybuildTree(vector<int>& preorder, vector<int>& inorder, int preorder_left, int preorder_right, int inorder_left, int inorder_right)
	{
		if (preorder_left > preorder_right)
			return nullptr;
		int preorder_root = preorder_left;
		int inorder_root = index[preorder[preorder_left]];

		int size = inorder_root - inorder_left;
		TreeNode* root = new TreeNode(inorder[inorder_root]);
		root->left = mybuildTree(preorder, inorder, preorder_left + 1, preorder_left + size, inorder_left, inorder_left + size);//inorder_root - 1);
		root->right = mybuildTree(preorder, inorder, preorder_left + size + 1, preorder_right, inorder_root + 1, inorder_right);
		return root;
	}

	TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
		int n = inorder.size();
		for (int i = 0; i < inorder.size(); ++i){
			index[inorder[i]] = i;
		}
		return mybuildTree(preorder, inorder, 0, n - 1, 0, n - 1);
	}
};