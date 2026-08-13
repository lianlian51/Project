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
	struct status
	{
		int val;
		ListNode* ptr;
		bool operator<(const status& down)const
		{
			return val > down.val;
		}
	};

	// 优先级队列处理
	priority_queue<status> q;

	ListNode* mergeKLists(vector<ListNode*>& lists) {
		// 1.遍历链表，将链表插入到优先级队列中，每个节点之后都有一条链表
		for (auto e : lists)
		{
			if (e)
				q.push({ e->val, e });
		}

		// 2.head标记头部，tail往后走，插入新的节点
		ListNode head, *tail = &head;
		while (!q.empty())
		{
			auto tmp = q.top();
			q.pop();
			// 这里给的是指针，不然连不起来
			tail->next = tmp.ptr;
			tail = tail->next;
			// 因为tmp是一个链表，处理完第一个节点之后，还需要处理之后的其他节点
			if (tmp.ptr->next)
			{
				q.push({ tmp.ptr->next->val, tmp.ptr->next });
			}
		}

		return head.next;
	}
};