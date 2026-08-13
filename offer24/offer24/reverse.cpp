#include <iostream>

struct ListNode
{
	int val;
	ListNode* m_pNext;
};

ListNode* ReverseList(ListNode* pHead)
{
	if (pHead == nullptr)
		return nullptr;

	ListNode* reverse = nullptr;
	ListNode* node = pHead;
	ListNode* prev = nullptr;

	while (node != nullptr)
	{
		ListNode* temp = node->m_pNext;

		if (temp == nullptr)
		{
			pHead = node;
		}
		node->m_pNext = prev;
		prev = node;
		node = temp;
	}
	return reverse;
}



int main()
{
	return 0;
}