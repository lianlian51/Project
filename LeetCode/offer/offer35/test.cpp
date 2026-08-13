#include <stdio.h>
#include <unistd.h>

#include <iostream>

#include "sigNode.hpp"

Node* copyRandomList(Node* head)
{
  Node* copy = nullptr;
  Node* copy_head = nullptr;
  Node* p = head;
  Node* tmp;
  // copy链表
  while(p)
  {
    tmp = p->next_;
    p->next_ = new Node(p->val_);
    p = p->next_;
    p->next_ = tmp;
    p = p->next_;
  }
  // 处理random
  p = head;
  while(p)
  {
    if(p->random_)
      p->next_->random_ = p->random_->next_;
    p = p->next_->next_;
  }
  // 拆开链表
  p = head;
  while(p)
  {
    if(copy == nullptr)
    {
      copy = p->next_;
      copy_head = copy;
    }
    else 
    {
      copy->next_ = p->next_;
      copy = copy->next_;

    }
    p->next_ = p->next_->next_;
    p = p->next_;
  }
  return copy_head;
}

int main()
{
  Node* p = CreateListNode();
  Node* q = copyRandomList(p);

  while(p)
  {
    std::cout << p->val_ << " ";
    p = p->next_;
  }
  std::cout << std::endl;

  while(q)
  {
    std::cout << q->val_ << " ";
    q = q->next_;
  }
  std::cout << std::endl;

  return 0;
}
