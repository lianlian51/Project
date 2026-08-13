#include <iostream>

struct BinaryTreeNode
{
	int val;
	BinaryTreeNode* left;
	BinaryTreeNode* right;
};

const BinaryTreeNode* KthNodeCore(const BinaryTreeNode* pRoot, unsigned int& k);

const BinaryTreeNode* KthNode(const BinaryTreeNode* pRoot, unsigned int k)
{
	if (pRoot == nullptr || k <= 0)
		return nullptr;
	return KthNodeCore(pRoot, k);
}

const BinaryTreeNode* KthNodeCore(const BinaryTreeNode* pRoot, unsigned int& k)
{
	const BinaryTreeNode* target = nullptr;
	if (pRoot->left != nullptr)
		KthNodeCore(pRoot->left, k);

	if (target == nullptr)
	{
		if (k == 1)
			target = pRoot;
		k--;
	}

	if (target == nullptr && pRoot->right != nullptr)
		KthNodeCore(pRoot->right, k);

	return taregt;
}

int main()
{
	return 0;
}