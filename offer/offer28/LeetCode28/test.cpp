#include <iostream>

struct BinaryTreeNode
{
	BinaryTreeNode* m_pLeft;
	BinaryTreeNode* m_pRight;
	int val;
};

bool isSymmetrical(BinaryTreeNode* root)
{
	return isSymmetrical(root, root);
}

bool isSymmetrical(BinaryTreeNode* pNode1, BinaryTreeNode* pNode2)
{
	if (pNode1 == nullptr && pNode2 == nullptr)
		return true;
	if (pNode1 == nullptr || pNode2 == nullptr)
		return false;
	if (pNode1->val != pNode2->val)
		return false;
	return isSymmetrical(pNode1->m_pLeft, pNode2->m_pRight) &&
		isSymmetrical(pNode1->m_pRight, pNode2->m_pLeft);
}


int main()
{
	return 0;
}