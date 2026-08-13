// 这里有一个非负整数数组 arr，你最开始位于该数组的起始下标 start 处。当你位于下标 i 处时，你可以跳到 i + arr[i] 或者 i - arr[i]。

// 请你判断自己是否能够跳到对应元素值为 0 的 任一 下标处。
// 输入：arr = [4,2,3,0,3,1,2], start = 5
// 输出：true
// 解释：
// 到达值为 0 的下标 3 有以下可能方案： 
// 下标 5 -> 下标 4 -> 下标 1 -> 下标 3 
// 下标 5 -> 下标 6 -> 下标 4 -> 下标 1 -> 下标 3

#include <stdio.h>
#include <unistd.h>

#include <iostream>
#include <vector>
#include <queue>

// 递归实现 Depth First search(DFS)
bool _canReach_1(std::vector<int>& arr, int start, std::vector<bool> &visited)
{
  int len = arr.size(); 
  if(start < 0 || start > len || arr[start])
    return false;

  if(arr[start] == 0)
    return true;

  return _canReach_1(arr, start + arr[start], visited) || _canReach_1(arr, start - arr[start], visited);
}

bool canReach_1(std::vector<int>& arr, int start)
{
  std::vector<bool> visited(arr.size(), false);
  return _canReach_1(arr, start, visited);
}


// 非递归实现 Breadth Frist Search(BFS)
bool canReach_2(std::vector<int>& arr, int start)
{
  int len = arr.size();
  std::vector<int> visited(len, false);
  std::queue<int> q{{start}};

  while(!q.empty())
  {
    auto cur = q.front();
    q.pop();
    if(cur < 0 || cur >= len || visited[start])
    {
      continue;
    }

    if(arr[cur] == 0)
    {
      return true;
    }

    visited[start] = true;

    q.push(cur + arr[start]);
    q.push(cur - arr[start]);
  }
  return false;
}

int main()
{
  std::vector<int> arr;
  arr.push_back(4);
  arr.push_back(3);
  arr.push_back(2);
  arr.push_back(0);
  arr.push_back(3);
  arr.push_back(1);
  arr.push_back(2);

  int start = 5;
  bool flag = canReach_1(arr, start);
  std::cout << "递归：" << flag << std::endl;

  flag = canReach_2(arr, start);
  std::cout << "非递归：" << flag << std::endl;

  return 0;
}

