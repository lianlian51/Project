#include <stdio.h>
#include <unistd.h>

#include <iostream>


#include "treenode.hpp"

bool _isSameTree(BTNode* p, BTNode* q)
{
  if(p == nullptr || q == nullptr)
    return p == q;
  if(p->data_ != q->data_)
    return false;
  return _isSameTree(p->left_, q->left_) && _isSameTree(p->right_, q->right_);
}

bool isSameTree(BTNode* p, BTNode* q)
{
  bool flag = _isSameTree(p, q);
  return flag;
}

void Create_1(pBTNode* node)
{
  BTNode* node1 = BuyNode(1);
  BTNode* node2 = BuyNode(2);
  BTNode* node3 = BuyNode(3);
  BTNode* node4 = BuyNode(4);

  (*node)->left_ = node1;
  (*node)->right_ = node2;
  node1->left_ = node3;
  node3->left_ = node4;
}

int main()
{
  pBTNode p, q;
  InitBTree(&p);
  InitBTree(&q);
  // p = Create_();  // 测试没问题的
  // q = Create_();
  Create_1(&p);
  Create_1(&q);

  bool flag = isSameTree(p, q);
  std::cout << flag << std::endl;
  return 0;
}
