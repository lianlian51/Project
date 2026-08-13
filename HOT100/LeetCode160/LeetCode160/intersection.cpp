/**
* Definition for singly-linked list.
* struct ListNode {
*     int val;
*     ListNode *next;
*     ListNode(int x) : val(x), next(NULL) {}
* };
*/
class Solution {
public:
	ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
		ListNode* pA = headA;
		ListNode* pB = headB;
		int a = 0, b = 0;

		while (pA != nullptr)
		{
			pA = pA->next;
			++a;
		}

		while (pB != nullptr)
		{
			pB = pB->next;
			++b;
		}

		int sub = a - b;
		pA = headA;
		pB = headB;
		if (sub > 0)
		{
			while (sub-- != 0)
			{
				pA = pA->next;
			}
		}
		else
		{
			while (sub++ != 0)
			{
				pB = pB->next;
			}
		}

		while (pA != nullptr && pB != nullptr)
		{
			if (pA == pB)
				return pA;
			pA = pA->next;
			pB = pB->next;
		}
		return nullptr;
	}
};