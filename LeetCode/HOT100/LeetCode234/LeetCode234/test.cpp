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
	ListNode* endOfListHalf(ListNode* head)
	{
		ListNode* fast = head;
		ListNode* slow = head;
		while (fast->next != nullptr && fast->next->next != nullptr)
		{
			fast = fast->next->next;
			slow = slow->next;
		}

		return slow;
	}

	ListNode* reverse(ListNode* head)
	{
		ListNode* tail = nullptr;
		ListNode* cur = head;

		while (cur != nullptr)
		{
			ListNode* temp = cur->next;
			cur->next = tail;
			tail = cur;
			cur = temp;
		}
		return tail;
	}


	bool isPalindrome(ListNode* head) {
		if (head == nullptr)
			return true;

		ListNode* core = endOfListHalf(head);
		ListNode* endOfHalf = reverse(core->next);

		ListNode* p1 = head;
		ListNode* p2 = endOfHalf;
		bool result = true;
		while (result && p1 != nullptr && p2 != nullptr)
		{
			if (p1->val != p2->val)
				result = false;

			p1 = p1->next;
			p2 = p2->next;
		}

		return result;
	}
};