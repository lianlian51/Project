#pragma once 

#include <stdio.h>
#include <unistd.h>
#include <malloc.h>
#include <assert.h>

#include <iostream>

typedef int DataType;

struct Node{
  Node* next_;
  Node* random_;
  DataType val_;

  Node(DataType data)
  {
    val_ = data;
    next_ = NULL;
    random_ = NULL;
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
  newNode->random_ = NULL;
  newNode->val_ = data;

  return newNode;
}

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
