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
	//unordered_map<TreeNode*, int> map; // 记录已经遍历过的
	unordered_map<TreeNode*, int> f, g;

	void dfs(TreeNode* root)
	{
		if (!root)
			return;
		dfs(root->left);
		dfs(root->right);
		f[root] = root->val + g[root->left] + g[root->right];
		g[root] = max(f[root->left], g[root->left]) + max(g[root->right], f[root->right]);
	}

	int rob(TreeNode* root) {
#if 0
		// 时间复杂度过大
		// 健壮性检测
		if (root == nullptr) return 0;
		if (root->left == nullptr && root->right == nullptr) return root->val;

		// 偷当前的
		int val1 = root->val;
		if (root->left) val1 += rob(root->left->left) + rob(root->left->right);
		if (root->right) val1 += rob(root->right->left) + rob(root->right->right);

		// 不偷当前的
		int val2 = rob(root->left) + rob(root->right);

		// 返回较大的一个
		return max(val1, val2);
#endif
#if 0
		if (root == nullptr) return 0;
		if (root->left == nullptr && root->right == nullptr) return root->val;

		// 偷当前的
		int val1 = root->val;
		if (root->left) val1 += rob(root->left->left) + rob(root->left->right);
		if (root->right) val1 += rob(root->right->left) + rob(root->right->right);
		if (map[root]) return map[root];

		// 不偷当前的
		int val2 = rob(root->left) + rob(root->right);
		map[root] = max(val1, val2); // 记录的是当前结点算出来的是偷盗的最大金额数

		// 返回较大的一个
		return max(val1, val2);

#endif
		dfs(root);
		return max(f[root], g[root]);
	}
};