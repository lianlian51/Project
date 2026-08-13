/**
* Definition for singly-linked list.
* struct ListNode {
*     int val;
*     ListNode *next;
*     ListNode() : val(0), next(nullptr) {}
*     ListNode(int x) : val(x), next(nullptr) {}
*     ListNode(int x, ListNode *next) : val(x), next(next) {}
* };
*/
class Solution {
public:
	ListNode* removeNthFromEnd(ListNode* head, int n) {
		ListNode* retHead = new ListNode(0, head);
		ListNode* del = retHead;
		ListNode* cur = head;

		while (n--)
		{
			cur = cur->next;
		}

		while (cur)
		{
			cur = cur->next;
			del = del->next;
		}

		del->next = del->next->next;

		ListNode* ret = retHead->next;
		return ret;
	}
};