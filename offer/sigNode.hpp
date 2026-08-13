#pragma once 

#include <stdio.h>
#include <unistd.h>
#include <malloc.h>
#include <assert.h>

#include <iostream>

typedef int DataType;

struct Node{
  Node* next_;
  // Node* random_;
  DataType val_;

  Node(DataType data)
  {
    val_ = data;
    next_ = NULL;
    // random_ = NULL;
  }
};

Node* BuyNode(DataType data)
{
  Node* newNode = (Node*)malloc(sizeof(Node));
  if(newNode == NULL)
  {
    std::cout << "创建结点失败" << std::endl;
    assert(newNode);
  }
  newNode->next_ = NULL;
  // newNode->random_ = NULL;
  newNode->val_ = data;

  return newNode;
}

#if 0
// 随机域random的创建
Node* CreateListNode()
{
  Node* list_ = BuyNode(7);
  Node* list1 = BuyNode(13);
  Node* list2 = BuyNode(11);
  Node* list3 = BuyNode(10);
  Node* list4 = BuyNode(1);

  list_->next_ = list1;
  list1->next_ = list2;
  list2->next_ = list3;
  list3->next_ = list4;

  list_->random_ = nullptr;
  list1->random_ = list_;
  list2->random_ = list4;
  list3->random_ = list2;
  list4->random_ = list_;

  return list_;
}
#endif
void listInit(Node* head)
{
  assert(head);
  head = NULL;
}

// 尾插
void PushBack(Node** head, DataType data)
{
  assert(head);
  Node* newNode = BuyNode(data);
  if(*head == NULL)
  {
    *head = newNode;
  }
  else 
  {
    Node* p = *head;
    while(p)
    {
      p = p->next_;
    }
    p->next_ = newNode;
  }
}

// 尾删
void PopBack(Node** head)
{
  assert(head);
  if(*head == NULL)
    return;
  else if((*head)->next_ == NULL)
  {
    free(*head);
    *head = NULL;
  }
  else 
  {
    Node* p = *head;
    Node* prev = nullptr;
    while(p->next_)
    {
      prev = p;
      p = p->next_;
    }
    prev->next_ = nullptr; // prev->next_ = p->next_;
    free(p);
  }
}

// 头插
void PushFront(Node** head, DataType data)
{
  assert(head);
  Node* newNode = BuyNode(data);
  newNode->next_ = *head;
  *head = newNode;
}

// 头删
void PopFront(Node** head)
{
  assert(head);
  if(*head == nullptr)
  {
    return; 
  }
  else if((*head)->next_ == nullptr)
  {
    free(*head);
    *head = nullptr;
  }
  else 
  {
    Node* oldNode = *head;
    *head = (*head)->next_;
    free(oldNode);
  }
}

// 删除任意位置的链表
void listErase(Node** head, DataType pos)
{
  Node* p = *head;
  int i = 0;
  while(p->next_ && i < pos - 1)
  {
    p = p->next_;
    i++;
  }

  if(!(p->next_) || i > pos - 1)
  {
    std::cout << "删除失败！" << std::endl;
  }
  else 
  {
    Node* q = p->next_;
    p->next_ = q->next_;
    free(q);
  }
}

// 添加任意位置的链表
void listInsert(Node** head, DataType data, int pos)
{
  Node* p = *head;
  int i = 0;
  while(p->next_ && i < pos - 1)
  {
    p = p->next_;
    i++;
  }
  if(!(p->next_) || i > pos - 1)
  {
    std::cout << "插入失败！" << std::endl;
  }
  else 
  {
    Node* q = p->next_;
    Node* newNode = BuyNode(data);
    p->next_ = newNode;
    newNode->next_ = q;
  }
}

// 链表长度
int listLength(Node* head)
{
  int count = 0;
  Node* p = head;
  while(p)
  {
    count++;
    p = p->next_;
  }
  return count;
}

// 寻找值为data的位置
Node* FindData(Node* head, DataType data)
{
  Node* p = head;
  while(p)
  {
    if(p->val_ == data)
      return p;
    p = p->next_;
  }
  return NULL;
}

// 销毁链表
void Destory(Node** head)
{
  Node* p = *head;
  while(p)
  {
    *head = p->next_;
    free(p);
    p = *head;
  }
}

// 打印链表
void Print(Node* head)
{
  Node* p = head;
  while(p)
  {
    std::cout << p->val_ << " ";
    p = p->next_;
  }
  std::cout << std::endl;
}
