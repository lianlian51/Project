#include <iostream>

struct BinaryTreeNode
{
	BinaryTreeNode* m_pLeft;
	BinaryTreeNode* m_pRight;
	int val;
};

void Mirror(BinaryTreeNode* root)
{
	if (root == nullptr)
		return;
	if (root->m_pLeft == nullptr && root->m_pRight == nullptr)
		return;

	BinaryTreeNode* pNode = root->m_pLeft;
	root->m_pLeft = root->m_pRight;
	root->m_pRight = pNode;

	if (root->m_pLeft)
		Mirror(root->m_pLeft);
	if (root->m_pRight)
		Mirror(root->m_pRight);
}




int main()
{
	return 0;
}