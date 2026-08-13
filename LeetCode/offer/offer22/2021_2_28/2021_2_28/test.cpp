/**
* Definition for singly-linked list.
* struct ListNode {
*     int val;
*     struct ListNode *next;
* };
*/


struct ListNode* getKthFromEnd(struct ListNode* head, int k){
	int count = 0;
	struct ListNode* cur = head;
	while (cur)
	{
		count++;
		cur = cur->next;
	}

	cur = head;
	for (int i = 0; i < count - k; i++)
		cur = cur->next;

	return cur;
}