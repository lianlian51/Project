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

void DeleteNode(ListNode** head)
{
  if(head == nullptr || *head == nullptr)
    return;

  ListNode* pPreNode = nullptr;
  ListNode* pNode = *head;

  while(pNode != nullptr)
  {
    ListNode* pNext = pNode->m_pNext;
    // flag控制要不要删除
    bool flag = false;
    if(pNext != nullptr && (pNext->m_nValue == pNode->m_nValue))
      flag = true;

    if(!flag)
    {
      pPreNode = pNode;
      pNode = pNode->m_pNext;
    }
    else 
    {
      int value = pNode->m_nValue;
      ListNode* del = pNode;
      while(del != nullptr && del->m_nValue == value)
      {
        pNext = del->m_pNext;
        delete del;
        del = nullptr;

        del = pNext;
      }
      // 将链表连接起来
      if(nullptr == pPreNode)
      {
        *head = pNext;
      }
      else 
      {
        pPreNode->m_pNext = pNext;
      }
      pNode = pNext;
    }
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
void Test(const char* testName, ListNode** pHead, int* expectedValues, int expectedLength)
{
  if(testName != nullptr)
    printf("%s begins: ", testName);

  DeleteNode(pHead);
  printf("result: ");
  PrintListNode(*pHead);
  printf("expected: ");
  for(int i = 0; i < expectedLength; ++i)
  {
    printf("%d ", expectedValues[i]);
  }
  std::cout << std::endl;
/*
  int index = 0;
  ListNode* pNode = *pHead;
  while(pNode != nullptr && index < expectedLength)
  {
    if(pNode->m_nValue != expectedValues[index])
      break;

    pNode = pNode->m_pNext;
    index++;

  }

  if(pNode == nullptr && index == expectedLength)
    printf("Passed.\n");
  else
    printf("FAILED.\n");
*/ 

}

// 某些结点是重复的
void Test1()
{
  ListNode* pNode1 = CreateListNode(1);
  ListNode* pNode2 = CreateListNode(2);
  ListNode* pNode3 = CreateListNode(3);
  ListNode* pNode4 = CreateListNode(3);
  ListNode* pNode5 = CreateListNode(4);
  ListNode* pNode6 = CreateListNode(4);

  ListNode* pNode7 = CreateListNode(5);

  ConnectListNodes(pNode1, pNode2);
  ConnectListNodes(pNode2, pNode3);
  ConnectListNodes(pNode3, pNode4);
  ConnectListNodes(pNode4, pNode5);
  ConnectListNodes(pNode5, pNode6);
  ConnectListNodes(pNode6, pNode7);

  ListNode* pHead = pNode1;

  int expectedValues[] = { 1, 2, 5  };
  Test("Test1", &pHead, expectedValues, sizeof(expectedValues) / sizeof(int));

  // DestroyList(pHead);
}




// 除了一个结点之外其他所有结点的值都相同
void Test3()
{
  ListNode* pNode1 = CreateListNode(1);
  ListNode* pNode2 = CreateListNode(1);
  ListNode* pNode3 = CreateListNode(1);
  ListNode* pNode4 = CreateListNode(1);
  ListNode* pNode5 = CreateListNode(1);
  ListNode* pNode6 = CreateListNode(1);
  ListNode* pNode7 = CreateListNode(2);

  ConnectListNodes(pNode1, pNode2);
  ConnectListNodes(pNode2, pNode3);
  ConnectListNodes(pNode3, pNode4);
  ConnectListNodes(pNode4, pNode5);
  ConnectListNodes(pNode5, pNode6);
  ConnectListNodes(pNode6, pNode7);

  ListNode* pHead = pNode1;

  int expectedValues[] = { 2  };
  Test("Test3", &pHead, expectedValues, sizeof(expectedValues) / sizeof(int));

  // DestroyList(pHead);
}




// 除了两个结点之外其他结点都成对出现
void Test6()
{
  ListNode* pNode1 = CreateListNode(1);
  ListNode* pNode2 = CreateListNode(1);
  ListNode* pNode3 = CreateListNode(2);
  ListNode* pNode4 = CreateListNode(3);
  ListNode* pNode5 = CreateListNode(3);
  ListNode* pNode6 = CreateListNode(4);
  ListNode* pNode7 = CreateListNode(5);
  ListNode* pNode8 = CreateListNode(5);

  ConnectListNodes(pNode1, pNode2);
  ConnectListNodes(pNode2, pNode3);
  ConnectListNodes(pNode3, pNode4);
  ConnectListNodes(pNode4, pNode5);
  ConnectListNodes(pNode5, pNode6);
  ConnectListNodes(pNode6, pNode7);
  ConnectListNodes(pNode7, pNode8);

  ListNode* pHead = pNode1;

  int expectedValues[] = { 2, 4  };
  Test("Test6", &pHead, expectedValues, sizeof(expectedValues) / sizeof(int));

  // DestroyList(pHead);
}

// 链表中只有两个不重复的结点
void Test7()
{
  ListNode* pNode1 = CreateListNode(1);
  ListNode* pNode2 = CreateListNode(2);

  ConnectListNodes(pNode1, pNode2);

  ListNode* pHead = pNode1;

  int expectedValues[] = { 1, 2  };
  Test("Test7", &pHead, expectedValues, sizeof(expectedValues) / sizeof(int));

  // DestroyList(pHead);
}

int main()
{
  Test1();
  Test3();
  Test6();
  Test7();
  return 0;
}
