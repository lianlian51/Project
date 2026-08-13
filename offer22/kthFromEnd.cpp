#include <iostream>
#include <stdio.h>


struct ListNode
{
  int val;
  ListNode* next;
  ListNode(int data)
    : val(data)
    , next(nullptr)
  {}
};

ListNode* FindKthToTail(ListNode* pListHead, unsigned int k)
{
  if(pListHead == nullptr || k == 0)
    return nullptr;

  ListNode* cur = pListHead;
  ListNode* prev = pListHead;
  for(int i = 0; i < (int)(k - 1); i++)
  {
    if(cur->next != nullptr)
      cur = cur->next;
    else 
      return nullptr;
  }
  while(cur->next != nullptr)
  {
    cur = cur->next;
    prev = prev->next;
  }
  return prev;
}

///////////////////////////////////测试代码
void PrintListNode(ListNode* head)
{
  ListNode* cur = head;
  while(cur)
  {
    std::cout << cur->val<< " ";
    cur = cur->next;

  }
  std::cout << std::endl;

}

ListNode* CreateListNode(int data)
{
  ListNode* node = new ListNode(data);
  if(node == nullptr)
    return nullptr;
  return node;

}

void ConnectListNodes(ListNode* node1, ListNode* node2)
{
  node1->next = node2;
  node2->next = nullptr;

}
void DestroyList(ListNode** head)
{
  while(*head)
  {
    ListNode* del = (*head);
    (*head) = (*head)->next;
    delete del;
    del = nullptr;

  }

}


// 测试要找的结点在链表中间
void Test1()
{
  printf("=====Test1 starts:=====\n");
  ListNode* pNode1 = CreateListNode(1);
  ListNode* pNode2 = CreateListNode(2);
  ListNode* pNode3 = CreateListNode(3);
  ListNode* pNode4 = CreateListNode(4);
  ListNode* pNode5 = CreateListNode(5);

  ConnectListNodes(pNode1, pNode2);
  ConnectListNodes(pNode2, pNode3);
  ConnectListNodes(pNode3, pNode4);
  ConnectListNodes(pNode4, pNode5);

  printf("expected result: 4.\n");
  ListNode* pNode = FindKthToTail(pNode1, 2);
  PrintListNode(pNode);

  // DestroyList(pNode1);
}

// 测试要找的结点是链表的尾结点
void Test2()
{
  printf("=====Test2 starts:=====\n");
  ListNode* pNode1 = CreateListNode(1);
  ListNode* pNode2 = CreateListNode(2);
  ListNode* pNode3 = CreateListNode(3);
  ListNode* pNode4 = CreateListNode(4);
  ListNode* pNode5 = CreateListNode(5);

  ConnectListNodes(pNode1, pNode2);
  ConnectListNodes(pNode2, pNode3);
  ConnectListNodes(pNode3, pNode4);
  ConnectListNodes(pNode4, pNode5);

  printf("expected result: 5.\n");
  ListNode* pNode = FindKthToTail(pNode1, 1);
  PrintListNode(pNode);

  //DestroyList(pNode1);
}

// 测试要找的结点是链表的头结点
void Test3()
{
  printf("=====Test3 starts:=====\n");
  ListNode* pNode1 = CreateListNode(1);
  ListNode* pNode2 = CreateListNode(2);
  ListNode* pNode3 = CreateListNode(3);
  ListNode* pNode4 = CreateListNode(4);
  ListNode* pNode5 = CreateListNode(5);

  ConnectListNodes(pNode1, pNode2);
  ConnectListNodes(pNode2, pNode3);
  ConnectListNodes(pNode3, pNode4);
  ConnectListNodes(pNode4, pNode5);

  printf("expected result: 1.\n");
  ListNode* pNode = FindKthToTail(pNode1, 5);
  PrintListNode(pNode);

  // DestroyList(pNode1);
}

// 测试空链表
void Test4()
{
  printf("=====Test4 starts:=====\n");
  printf("expected result: nullptr.\n");
  ListNode* pNode = FindKthToTail(nullptr, 100);
  PrintListNode(pNode);
}

// 测试输入的第二个参数大于链表的结点总数
void Test5()
{
  printf("=====Test5 starts:=====\n");
  ListNode* pNode1 = CreateListNode(1);
  ListNode* pNode2 = CreateListNode(2);
  ListNode* pNode3 = CreateListNode(3);
  ListNode* pNode4 = CreateListNode(4);
  ListNode* pNode5 = CreateListNode(5);

  ConnectListNodes(pNode1, pNode2);
  ConnectListNodes(pNode2, pNode3);
  ConnectListNodes(pNode3, pNode4);
  ConnectListNodes(pNode4, pNode5);

  printf("expected result: nullptr.\n");
  ListNode* pNode = FindKthToTail(pNode1, 6);
  PrintListNode(pNode);

  // DestroyList(pNode1);
}

int main()
{
  Test1();
  Test2();
  Test3();
  Test4();
  Test5();
  return 0;
}
