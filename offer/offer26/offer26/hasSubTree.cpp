#include <iostream>

struct BinaryTreeNode
{
	BinaryTreeNode* m_pLeft;
	BinaryTreeNode* m_pRight;
	double m_dbValue;
};

bool Equal(double num1, double num2);
bool DoesTree1HaveTree2(BinaryTreeNode* pHead1, BinaryTreeNode* pHead2);

bool HasSubTree(BinaryTreeNode* pHead1, BinaryTreeNode* pHead2)
{
	bool result = false;
	if (pHead1 != nullptr && pHead2 != nullptr)
	{
		if (Equal(pHead1->m_dbValue, pHead2->m_dbValue))
		{
			result = DoesTree1HaveTree2(pHead1, pHead2);
		}
		if (!result)
			result = HasSubTree(pHead1->m_pLeft, pHead2);
		if (!result)
			result = HasSubTree(pHead1->m_pRight, pHead2);
	}
	return result;
}

bool Equal(double num1, double num2)
{
	if (num1 - num2 < 0.0000001 && num1 - num2 > -0.0000001)
		return true;
	else
		return false;
}

bool DoesTree1HaveTree2(BinaryTreeNode* pHead1, BinaryTreeNode* pHead2)
{
	if (pHead2 == nullptr)
		return true;
	if (pHead1 == nullptr)
		return false;

	if (!Equal(pHead1->m_dbValue, pHead2->m_dbValue))
		return false;

	return DoesTree1HaveTree2(pHead1->m_pLeft, pHead2->m_pLeft) &&
		DoesTree1HaveTree2(pHead1->m_pRight, pHead2->m_pRight);
}


int main()
{
	return 0;
}