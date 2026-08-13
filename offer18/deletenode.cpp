#include <iostream>


struct ListNode
{
  int m_nValue;
  ListNode* m_pNext;
  ListNode(int data)
    : m_nValue(data)
    , m_pNext(nullptr)
  {}
};

void DeleteNode(ListNode** head, ListNode* pDeleted)
{
  if(head == nullptr || pDeleted == nullptr)
    return;

  if(pDeleted->m_pNext != nullptr)
  {
    // 删除节点不是尾结点
    ListNode* pNext = pDeleted->m_pNext;
    pDeleted->m_nValue = pNext->m_nValue;
    pDeleted->m_pNext = pNext->m_pNext;
    delete pNext;
    pNext = nullptr;
  }
  else if(*head == pDeleted)
  {
    // 删除头结点
    delete pDeleted;
    pDeleted = nullptr;
    *head = nullptr;
  }
  else 
  {
    // 删除尾结点
    ListNode* cur = (*head);
    while(cur->m_pNext != pDeleted)
    {
      cur = cur->m_pNext;
    }
    cur->m_pNext = nullptr;
    delete pDeleted;
    pDeleted = nullptr;
  }
}

/////////////////////////////////////////////测试代码
void PrintListNode(ListNode* head)
{
  ListNode* cur = head;
  while(cur)
  {
    std::cout << cur->m_nValue << " ";
    cur = cur->m_pNext;
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
  node1->m_pNext = node2;
  node2->m_pNext = nullptr;
}
void DestroyList(ListNode** head)
{
  while(*head)
  {
    ListNode* del = (*head);
    (*head) = (*head)->m_pNext;
    delete del;
    del = nullptr;
  }
}

void Test(ListNode* head, ListNode* pDel)
{
  printf("the original is : ");
  PrintListNode(head);
  printf("the node to be deleted is :");
  std::cout << pDel->m_nValue << std::endl;
  DeleteNode(&head, pDel);
  printf("the result is :");
  PrintListNode(head);
}



// 链表中有多个结点，删除中间的结点
void Test1()
{
  ListNode* pNode1 = CreateListNode(1);
  ListNode* pNode2 = CreateListNode(2);
  ListNode* pNode3 = CreateListNode(3);
  ListNode* pNode4 = CreateListNode(4);
  ListNode* pNode5 = CreateListNode(5);

  ConnectListNodes(pNode1, pNode2);
  ConnectListNodes(pNode2, pNode3);
  ConnectListNodes(pNode3, pNode4);
  ConnectListNodes(pNode4, pNode5);

  Test(pNode1, pNode3);

  // DestroyList(pNode1);
}

// 链表中有多个结点，删除尾结点
void Test2()
{
  ListNode* pNode1 = CreateListNode(1);
  ListNode* pNode2 = CreateListNode(2);
  ListNode* pNode3 = CreateListNode(3);
  ListNode* pNode4 = CreateListNode(4);
  ListNode* pNode5 = CreateListNode(5);

  ConnectListNodes(pNode1, pNode2);
  ConnectListNodes(pNode2, pNode3);
  ConnectListNodes(pNode3, pNode4);
  ConnectListNodes(pNode4, pNode5);

  Test(pNode1, pNode5);

  // DestroyList(pNode1);
}

// 链表中有多个结点，删除头结点
void Test3()
{
  ListNode* pNode1 = CreateListNode(1);
  ListNode* pNode2 = CreateListNode(2);
  ListNode* pNode3 = CreateListNode(3);
  ListNode* pNode4 = CreateListNode(4);
  ListNode* pNode5 = CreateListNode(5);

  ConnectListNodes(pNode1, pNode2);
  ConnectListNodes(pNode2, pNode3);
  ConnectListNodes(pNode3, pNode4);
  ConnectListNodes(pNode4, pNode5);

  Test(pNode1, pNode1);

  // DestroyList(pNode1);
}

// 链表中只有一个结点，删除头结点
void Test4()
{
  ListNode* pNode1 = CreateListNode(1);

  Test(pNode1, pNode1);
}





int main()
{
  Test1();
  Test2();
  Test3();
  Test4();
  return 0;
}
