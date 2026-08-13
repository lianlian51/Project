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
	void flatten(TreeNode* root) {
		vector<TreeNode*> l;
		preorder(root, l);
		for (int i = 1; i < (int)l.size(); ++i)
		{
			TreeNode* prev = l[i - 1], *cur = l[i];
			prev->left = nullptr;
			prev->right = cur;
		}
	}

	void preorder(TreeNode* root, vector<TreeNode*>& l)
	{
		if (root != nullptr)
		{
			l.push_back(root);
			preorder(root->left, l);
			preorder(root->right, l);
		}
	}
};

// µü´ú
class Solution {
public:
	void flatten(TreeNode* root) {
		auto v = vector<TreeNode*>();
		auto stk = stack<TreeNode*>();
		TreeNode *node = root;
		while (node != nullptr || !stk.empty()) {
			while (node != nullptr) {
				v.push_back(node);
				stk.push(node);
				node = node->left;
			}
			node = stk.top(); stk.pop();
			node = node->right;
		}
		int size = v.size();
		for (int i = 1; i < size; i++) {
			auto prev = v.at(i - 1), curr = v.at(i);
			prev->left = nullptr;
			prev->right = curr;
		}
	}
};
