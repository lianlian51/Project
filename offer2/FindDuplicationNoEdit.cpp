#include <iostream>
// 面试题3（二）：不修改数组找出重复的数字
// 题目：在一个长度为n+1的数组里的所有数字都在1到n的范围内，所以数组中至
// 少有一个数字是重复的。请找出数组中任意一个重复的数字，但不能修改输入的
// 数组。例如，如果输入长度为8的数组{2, 3, 5, 4, 3, 2, 6, 7}，那么对应的
// 输出是重复的数字2或者3。

int countRange(const int* numbers, int length, int left, int right)
{
  if(numbers == nullptr)
    return 0;
  int count = 0;
  for(int i = 0; i < length; ++i){
    if(numbers[i] >= left && numbers[i] <= right){
      count++;
    }
  }
  return count;
}

int GetDuplication(const int* numbers, int length)
{
  if(numbers == nullptr || length < 0){
    return -1;
  }
  int left = 1;
  int right = length - 1;
  while(left <= right)
  {
    int middle = ((right - left)>>1) + left;

    int count = countRange(numbers, length, left, middle);

    if(left == right){
      if(count > 1)
      {
        return left;
      }
      else 
        break;
    }
    if(count > (middle - left + 1)){
      right = middle;
    }
    else {
      left = middle + 1;
    }
  }
  return -1;
}
// 测试代码
void test(const char* testname, const int* numbers, int numberslength, int* expected, int expectedlength)
{
  int result = GetDuplication(numbers, numberslength);
  for(int i = 0; i < expectedlength; ++i){
    if(expected[i] == result){
      std::cout << testname << " Passed!" << std::endl;
      return;
    }
  }
  std::cout << testname << " Failed!" << std::endl;
}

// 多个重复的数字
void test1()
{
  int numbers[] = { 2, 3, 5, 4, 3, 2, 6, 7  };
  int duplications[] = { 2, 3  };
  test("test1", numbers, sizeof(numbers) / sizeof(int), duplications, sizeof(duplications) / sizeof(int));
}

// 一个重复的数字
void test2()
{
  int numbers[] = { 3, 2, 1, 4, 4, 5, 6, 7  };
  int duplications[] = { 4  };
  test("test2", numbers, sizeof(numbers) / sizeof(int), duplications, sizeof(duplications) / sizeof(int));
}

// 重复的数字是数组中最小的数字
void test3()
{
  int numbers[] = { 1, 2, 3, 4, 5, 6, 7, 1, 8  };
  int duplications[] = { 1  };
  test("test3", numbers, sizeof(numbers) / sizeof(int), duplications, sizeof(duplications) / sizeof(int));
}

// 重复的数字是数组中最大的数字
void test4()
{
  int numbers[] = { 1, 7, 3, 4, 5, 6, 8, 2, 8  };
  int duplications[] = { 8  };
  test("test4", numbers, sizeof(numbers) / sizeof(int), duplications, sizeof(duplications) / sizeof(int));
}

// 数组中只有两个数字
void test5()
{
  int numbers[] = { 1, 1  };
  int duplications[] = { 1  };
  test("test5", numbers, sizeof(numbers) / sizeof(int), duplications, sizeof(duplications) / sizeof(int));
}

// 重复的数字位于数组当中
void test6()
{
  int numbers[] = { 3, 2, 1, 3, 4, 5, 6, 7  };
  int duplications[] = { 3  };
  test("test6", numbers, sizeof(numbers) / sizeof(int), duplications, sizeof(duplications) / sizeof(int));
}

// 多个重复的数字
void test7()
{
  int numbers[] = { 1, 2, 2, 6, 4, 5, 6  };
  int duplications[] = { 2, 6  };
  test("test7", numbers, sizeof(numbers) / sizeof(int), duplications, sizeof(duplications) / sizeof(int));
}

// 一个数字重复三次
void test8()
{
  int numbers[] = { 1, 2, 2, 6, 4, 5, 2  };
  int duplications[] = { 2  };
  test("test8", numbers, sizeof(numbers) / sizeof(int), duplications, sizeof(duplications) / sizeof(int));
}

// 没有重复的数字
void test9()
{
  int numbers[] = { 1, 2, 6, 4, 5, 3  };
  int duplications[] = { -1  };
  test("test9", numbers, sizeof(numbers) / sizeof(int), duplications, sizeof(duplications) / sizeof(int));
}

// 无效的输入
void test10()
{
  int* numbers = nullptr;
  int duplications[] = { -1  };
  test("test10", numbers, 0, duplications, sizeof(duplications) / sizeof(int));
}





int main()
{
  test1();
  test2();
  test3();
  test4();
  test5();
  test6();
  test7();
  test8();
  test9();
  test10();
  return 0;
}
