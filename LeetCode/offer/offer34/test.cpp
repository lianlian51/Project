#include <stdio.h>
#include <unistd.h>

#include <iostream>
#include <vector>

#include "../../treenode.hpp"

int ans = 0;
std::vector<int> v;

void _pathSum(std::vector<std::vector<int>>& vv, BTNode* root, int sum)
{
  if(root == NULL)
    return;
  ans += root->data_;
  v.push_back(root->data_);
  if(ans == sum && root->left_ == NULL && root->right_ == NULL)
    vv.push_back(v);
  _pathSum(vv, root->left_, sum);
  _pathSum(vv, root->right_, sum);
  v.pop_back();
  ans -= root->data_;
}

std::vector<std::vector<int>> pathSum(BTNode* root, int sum)
{
  std::vector<std::vector<int>> vv;
  _pathSum(vv, root, sum);
  return vv;
}

int main()
{
  BTNode* root;
  root = Create_2();
  std::vector<std::vector<int>> nums = pathSum(root, 22);
  for(int i = 0; i < nums.size(); i++)
  {
    for(int j = 0; j < nums[i].size(); j++)
    {
      std::cout << nums[i][j] << " ";
    }
    std::cout << std::endl;
  }
  return 0;
}
