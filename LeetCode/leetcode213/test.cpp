// leetcode213.打家劫舍② 
// https://leetcode-cn.com/problems/house-robber-ii/

#include <stdio.h>
#include <unistd.h>
#include <math.h>

#include <iostream>
#include <vector>

int robRange(std::vector<int>& nums, int start, int end)
{
  if(end > nums.size())
    return 0;
  int cur_ = 0;
  int prev_ = 0;

  for(int i = start; i <= end; i++)
  {
    int temp = cur_;
    cur_ = fmax(cur_, prev_ + nums[i]);
    prev_ = temp;
  }
  return cur_;
}

int rob(std::vector<int>& nums)
{
  if(nums.size() == 0)
    return 0;
  if(nums.size() == 1)
    return nums[0];
  return fmax(robRange(nums, 0, nums.size() - 2), robRange(nums, 1, nums.size() - 1));
}

int main()
{
  std::vector<int> nums({1,2,3,1});
  std::cout << rob(nums) << std::endl;
  return 0;
}
