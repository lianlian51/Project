
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
	ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
		int ntake = 0;
		ListNode* head = nullptr, *tail = nullptr;
		while (l1 || l2)
		{
			// 处理掉l1或者l2不存在的情况
			int n1 = l1 ? l1->val : 0;
			int n2 = l2 ? l2->val : 0;
			int sum = n1 + n2 + ntake;
			if (!head)
			{
				// 第一个节点需要给head和tail赋值
				head = tail = new ListNode(sum % 10);
			}
			else
			{
				tail->next = new ListNode(sum % 10);
				tail = tail->next;
			}
			// 记录进位，这里直接除10，不要直接赋值
			ntake = sum / 10;
			// 让l1和来l2往后走
			if (l1)
				l1 = l1->next;
			if (l2)
				l2 = l2->next;
		}
		// 处理进位
		if (ntake > 0)
			tail->next = new ListNode(ntake);
		return head;
	}
};