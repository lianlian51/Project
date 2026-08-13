#include <stdio.h>

int MinNums(int* nums, int length)
{
  if(nums == NULL || length <= 0)
    return -1;

  int index1 = 0;
  int index2 = length - 1;
  int indexmid = index1;
  while(index1 <= index2)
  {
    if(index2 - index1 == 1)
    {
      index2 = indexmid;
      break;
    }
    indexmid = (index1 + index2) / 2;
    // 刚才写的代码无法处理index1，index2，indexmid是一样的情况
    // 对于这种情况，那么就直接遍历数组得到结果
    if(nums[index1] == nums[index2] && nums[index1] == nums[indexmid]){
      int temp = nums[index1];
      for(int i = index1 + 1; i <= index2; ++i){
        if(nums[i] < temp)
          temp = nums[i];
      }
      return temp;
    }
    if(nums[index1] <= nums[indexmid])
    {
      index1 = indexmid; 
    }
    else {
      index2 = indexmid;
    }
  }
  return nums[indexmid];
}


int main()
{
  int nums[] = {3,4,5,1,2};
  printf("%d\n", MinNums(nums, 5));
  int nums1[] = { 3, 4, 5, 1, 1, 2  };
  printf("%d\n", MinNums(nums1, 6));
  int nums2[] = { 1, 0, 1, 1, 1 };
  printf("%d\n", MinNums(nums2, 5));
  return 0;
}
