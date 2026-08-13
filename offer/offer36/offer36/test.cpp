#include <iostream>

struct BinaryTreeNode
{
	BinaryTreeNode* left;
	BinaryTreeNode* right;
	int val;

	BinaryTreeNode(const int data = 0)
		: left(nullptr)
		, right(nullptr)
		, val(data)
	{}
};

void ConvertNode(BinaryTreeNode* pRoot, BinaryTreeNode** pList);

BinaryTreeNode* Convert(BinaryTreeNode* pRoot)
{
	BinaryTreeNode* pList = nullptr;
	ConvertNode(pRoot, &pList);

	// 此时PList指向的是双向链表的尾部
	BinaryTreeNode* pNode = pList;

	while (pNode != nullptr && pNode->left != nullptr)
		pNode = pNode->left;

	return pNode;
}

void ConvertNode(BinaryTreeNode* pRoot, BinaryTreeNode** pList)
{
	if (pRoot == nullptr)
		return;
	BinaryTreeNode* pCur = pRoot;
	if (pCur->left)
		ConvertNode(pRoot->left, pList);
	pCur->left = *pList;
	if (*pList != nullptr)
		(*pList)->right = pCur;

	*pList = pCur;

	if (pCur->right)
		ConvertNode(pRoot->right, pList);
}

BinaryTreeNode* Create1()
{
	BinaryTreeNode* node4 = new BinaryTreeNode(4);
	BinaryTreeNode* node6 = new BinaryTreeNode(6);
	BinaryTreeNode* node8 = new BinaryTreeNode(8);
	BinaryTreeNode* node10 = new BinaryTreeNode(10);
	BinaryTreeNode* node12 = new BinaryTreeNode(12);
	BinaryTreeNode* node14 = new BinaryTreeNode(14);
	BinaryTreeNode* node16 = new BinaryTreeNode(16);

	node10->left = node6;
	node10->right = node14;
	node6->left = node4;
	node6->right = node8;
	node14->left = node12;
	node14->right = node16;

	return node10;
}

void InOrder(BinaryTreeNode* pNode)
{
	if (pNode)
	{
		InOrder(pNode->left);
		std::cout << pNode->val << " ";
		InOrder(pNode->right);
	}
}



int main()
{
	BinaryTreeNode* p = Create1();
	InOrder(p);
	std::cout << std::endl;

	p = Convert(p);
	while (p != nullptr)
	{
		std::cout << p->val << " ";
		p = p->right;
	}
	std::cout << std::endl;

	return 0;
}