#include <iostream>
#include <string.h>

bool Increment(char* number);
void PrintNumber(char* arr);

void Print1ToMax1(int n)
{
  if(n <= 0)
    return;
  char* arr = new char[n + 1];
  memset(arr, '0', n);
  arr[n] = '\0';

  while(!Increment(arr))
  {
    PrintNumber(arr);
  }

  delete[] arr;
}
bool Increment(char* number)
{
  bool flag = false;
  int length = strlen(number);
  int nTakeOver = 0;
  for(int i = length - 1; i >= 0; --i)
  {
    // 得出末尾数字
    int nSum = number[i] - '0' + nTakeOver;
    // 只对末尾数字++
    if(length - 1 == i)
      nSum++;

    // 如果i位置数字大于10,则对其进行进位操作
    if(nSum >= 10)
    {
      // 如果访问到0位置元素，则表示溢出
      if(i == 0)
      {
        flag = true;
      }
      else 
      {
        nSum -= 10;
        nTakeOver = 1;
        number[i] = nSum + '0';
      }
    }
    else 
    {
      number[i] = nSum + '0';
      break;
    }
  }
  return flag;
}
void PrintNumber(char* arr)
{
  // 将字符数组的第一个非0的数字开始打印
  int length = strlen(arr);
  bool isbegin = true;
  for(int i = 0; i < length; ++i)
  {
    // 判断是不是非0
    if(isbegin && arr[i] != '0')
      isbegin = false;

    // 打印非0之后的数字
    if(!isbegin)
    {
      printf("%c", arr[i]);
    }
  }
  printf("\t");
}
void PrintRecur(char*number, int n, int index);
void Print1ToMax2(int n)
{
  if(n <= 0)
    return;

  char* number = new char[n + 1];
  number[n] = '\0';

  for(int i = 0; i < 10; ++i)
  {
    number[0] = i + '0';
    PrintRecur(number, n, 0);
  }
  delete[] number;
}
void PrintRecur(char*number, int n, int index)
{
  if(index == n - 1)
  {
    PrintNumber(number);
    return;
  }

  for(int i = 0; i < 10; ++i)
  {
    number[index + 1] = i + '0';
    PrintRecur(number, n, index + 1);
  }
}

void Test(int n)
{
  printf("Test %d begins:\n", n);
  Print1ToMax1(n);
  Print1ToMax2(n);
  printf("Test %d end\n", n);
}

int main()
{
  Test(1);
  Test(2);
  Test(-1);
  return 0;
}
