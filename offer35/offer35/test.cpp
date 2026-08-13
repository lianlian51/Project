#include <iostream>

struct ComplexListNode
{
	int val;
	ComplexListNode* next;
	ComplexListNode* sibling;

	ComplexListNode(const int& data = 0)
		: val(data)
		, next(nullptr)
		, sibling(nullptr)
	{}
};


void CloneNodes(ComplexListNode* pHead)
{
	ComplexListNode* pNode = pHead;
	while (pNode != nullptr)
	{
		ComplexListNode* clone = new ComplexListNode();
		clone->next = pNode->next;
		clone->val = pNode->val;
		clone->sibling = nullptr;

		pNode->next = clone;
		pNode = clone->next;
	}
}

void Connect(ComplexListNode* pHead)
{
	ComplexListNode* pNode = pHead;
	while (pNode != nullptr)
	{
		ComplexListNode* pClone = pNode->next;
		if (pNode->sibling != nullptr)
			pClone->sibling = pNode->sibling->next;

		pNode = pClone->next;
	}
}

ComplexListNode* Reconnect(ComplexListNode* pHead)
{
	ComplexListNode* pNode = pHead;
	ComplexListNode* pClone = nullptr;
	ComplexListNode* pCloneHead = nullptr;

	if (pNode != nullptr)
	{
		pClone = pCloneHead = pNode->next;
		pNode->next = pClone->next;
		pNode = pNode->next;
	}

	while (pNode != nullptr)
	{
		pClone->next = pNode->next;
		pClone = pClone->next;

		pNode->next = pClone->next;
		pNode = pNode->next;
	}

	return pCloneHead;
}

ComplexListNode* Copy(ComplexListNode* pHead)
{
	CloneNodes(pHead);
	Connect(pHead);
	return Reconnect(pHead);
}

void Print(ComplexListNode* pHead)
{
	if (pHead == nullptr)
		return;

	ComplexListNode* pNode = pHead;
	while (pNode)
	{
		std::cout << "node->val:" << pNode->val << "\t";
		if (pNode->next)
			std::cout << "node->next:" << pNode->next->val << "\t";
		if (pNode->sibling)
			std::cout << "node->sibling:" << pNode->sibling->val << "\t";
		std::cout << std::endl;
		pNode = pNode->next;
	}
}



typedef ComplexListNode Node;
ComplexListNode* Create1()
{
	Node* node1 = new Node(1);
	Node* node2 = new Node(2);
	Node* node3 = new Node(3);
	Node* node4 = new Node(4);
	Node* node5 = new Node(5);

	node1->next = node2;
	node2->next = node3;
	node3->next = node4;
	node4->next = node5;

	node1->sibling = node3;
	node2->sibling = node5;
	node4->sibling = node2;

	return node1;
}

Node* Create2()
{
	Node* node1 = new Node(1);
	Node* node2 = new Node(2);
	Node* node3 = new Node(3);
	Node* node4 = new Node(4);
	Node* node5 = new Node(5);
	Node* node6 = new Node(6);

	node1->next = node2;
	node2->next = node3;
	node3->next = node4;
	node4->next = node5;
	node5->next = node6;

	node2->sibling = node4;
	node4->sibling = node2;

	node5->sibling = node5;
	return node1;
}




int main()
{
	/*
	Node* p = Create1();
	Print(p);
	std::cout << std::endl;
	p = Copy(p);
	Print(p);
	std::cout << std::endl;
	*/

	Node* p = Create2();
	Print(p);
	std::cout << std::endl;
	p = Copy(p);
	Print(p);
	std::cout << std::endl;

	return 0;
}