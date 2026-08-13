// 判断二叉树是不是镜像二叉树，镜像不仅是要结构对称，而且值也要一样
 
#include <stdio.h>
#include <unistd.h>

#include <iostream>

#include "treenode.hpp"

bool _mirrorTree(BTNode* left, BTNode* right)
{
  if(left == NULL && right == NULL)
    return true;

  if((left == NULL && right != NULL) || (left != NULL && right == NULL))
    return false;

  if(left->data_ == right->data_)
    return _mirrorTree(left->left_, right->right_) && _mirrorTree(left->right_, right->left_);

  return false;
}

bool mirrorTree(BTNode* root)
{
  if(root == NULL)
    return true;
  return _mirrorTree(root->left_, root->right_);
}

int main()
{
  pBTNode root = Create_1();
  std::cout << mirrorTree(root) << std::endl;

  root = Create_2();
  std::cout << mirrorTree(root) << std::endl;
  return 0;
}
