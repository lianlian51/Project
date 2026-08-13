// 实现二分查找的加强版本
// 给定一个数组A及其大小n，同时给定需要查找的元素值x，已知数组A是由一个排过序的数组向左移位了一定长度得到的，请返回x在现数组的位置(位置从零开始)。保证数组中元素互异。
// 测试样例：
// [6,1,2,3,4,5],6,6
// 返回：0

// 处理这道题的思想就是在顺序的位置找

#include <stdio.h>
#include <unistd.h>

#include <iostream>
#include <vector>

int findElement(std::vector<int> v, int x)
{
  int left = 0;
  int right = v.size() - 1;
  while(left <= right)
  {
    int mid = (left + right) / 2;
    if(v[mid] == x)
    {
      return mid;
    }
    if(v[left] < v[mid])
    {
      if(v[left] <= x && x < v[mid])  
      {
        right = mid - 1;
      }
      else 
      {
        left = mid + 1;
      }
    }
    else 
    {
      if(v[mid] < x && x < v[right])
      {
        left = mid + 1;
      }
      else 
      {
        right = mid - 1;
      }
    }
  }
  return -1;
}

int main()
{
  std::vector<int> v({6, 1, 2, 3, 4, 5});
  int pos = findElement(v, 6);
  std::cout << pos << std::endl;
  return 0;
}
