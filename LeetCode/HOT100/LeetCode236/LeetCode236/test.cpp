/**
* Definition for a binary tree node.
* struct TreeNode {
*     int val;
*     TreeNode *left;
*     TreeNode *right;
*     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
* };
*/
class Solution {
public:
	TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
		if (q == root || p == root)
			return root;

		if (root != nullptr)
		{
			TreeNode* lNode = lowestCommonAncestor(root->left, p, q);
			TreeNode* rNode = lowestCommonAncestor(root->right, p, q);

			if (lNode != nullptr && rNode != nullptr)
				return root;
			else if (lNode == nullptr)
				return rNode;
			else if (rNode == nullptr)
				return lNode;
		}

		return nullptr;
	}
};