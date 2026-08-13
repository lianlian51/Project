#include <stdio.h>
#include <unistd.h>
#include <math.h>

#include <iostream>

#include "../treenode.hpp"

#if 0
// 方法一
int dfs(BTNode* root, int& a, int& b)
{
  if(!root)
  {
    a = 0;
    b = 0;
    return 0;
  }

  int la, lb;
  int ra, rb;
  int c, d;
  c = dfs(root->left_, la, lb);
  d = dfs(root->right_, ra, rb);
  a = lb + 1;
  b = ra + 1;
  return fmax(fmax(c, d), fmax(a, b));
}

int longestzigzag(BTNode* root)
{
  int a,b;
  int c = dfs(root, a, b);
  return fmax(fmax(a, b), c);
}
#endif 

// 方法二
int ans = 0;  // 记录最后的长度

void dfs(BTNode* root, int dir, int dis)
{
  if(!root)
    return;
  ans = fmax(ans, dis);
  if(dir)  // root的是右孩子，那么就要找左孩子存不存在
  {
    dfs(root->left_, 0, dis + 1);
    dfs(root->right_, 0, dis);
  }
  else 
  {
    // root是左孩子
    dfs(root->left_, 0, dis);
    dfs(root->right_, 1, dis + 1);
  }
}

int longestzigzag(BTNode* root)
{
  dfs(root, 0, 1); // 0代表左孩子，1代表右孩子
  dfs(root, 1, 1); // 第三个参数表示路径长度
  return ans;
}


int main()
{
  pBTNode node;
  node = Create_();
  std::cout << longestzigzag(node) << std::endl;
  return 0;
}
