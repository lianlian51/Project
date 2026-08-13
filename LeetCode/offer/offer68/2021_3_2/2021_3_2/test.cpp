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
		while (root)
		{
			// 因为是二叉搜索树，所以可以根据值来寻找
			// 节点的值大于p和q的，那么就在左子树里面寻找
			if (root->val > p->val && root->val > q->val)
			{
				root = root->left;
			}
			else if (root->val < p->val && root->val < q->val)
			{
				root = root->right;
			}
			else
			{
				// 对于一个在左子树一个在右子树，那么就返回root
				return root;
			}
		}
		return NULL;
	}
};