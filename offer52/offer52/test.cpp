#include <iostream>

struct ListNode
{
	int val;
	ListNode* next;
};

unsigned int GetListLength(ListNode* pHead);

ListNode* FindFirstCommonNode(ListNode *pHead1, ListNode *pHead2)
{
	unsigned int l1 = GetListLength(pHead1);
	unsigned int l2 = GetListLength(pHead2);
	int l12 = l1 - l2;

	ListNode* pL = pHead1;
	ListNode* pS = pHead2;
	if (l12 < 0)
	{
		pL = pHead2;
		pS = pHead1;
		l12 = l2 - l1;
	}

	for (int i = 0; i < l12; ++i)
		pL = pL->next;

	while (pL != nullptr && pS != nullptr && pL != pS)
	{
		pL = pL->next;
		pS = pS->next;
	}
	return pS;
}


unsigned int GetListLength(ListNode* pHead)
{
	unsigned int ret = 0;
	ListNode* cur = pHead;
	while (cur != nullptr)
	{
		cur = cur->next;
		++ret;
	}
	return ret;
}


int main()
{
	return 0;
}