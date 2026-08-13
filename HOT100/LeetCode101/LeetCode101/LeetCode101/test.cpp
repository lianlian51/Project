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
// µÝ¹é
class Solution {
public:
	bool check(TreeNode* left, TreeNode* right)
	{
		if (!left && !right){
			return true;
		}
		if (!left || !right)
			return false;

		return left->val == right->val && check(left->left, right->right) && check(left->right, right->left);
	}

	bool isSymmetric(TreeNode* root) {
		return check(root, root);
	}
};

// µü´ú
class Solution {
public:
	bool check(TreeNode *u, TreeNode *v) {
		queue <TreeNode*> q;
		q.push(u); q.push(v);
		while (!q.empty()) {
			u = q.front(); q.pop();
			v = q.front(); q.pop();
			if (!u && !v) continue;
			if ((!u || !v) || (u->val != v->val)) return false;

			q.push(u->left);
			q.push(v->right);

			q.push(u->right);
			q.push(v->left);
		}
		return true;
	}

	bool isSymmetric(TreeNode* root) {
		return check(root, root);
	}
};
