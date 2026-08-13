#include <stdio.h>

void Reorder1(int* pData, unsigned int length)
{
  if(pData == NULL|| length == 0)
    return;

  int* pBegin = pData;
  int* pEnd = pData + length - 1;
  while(pBegin < pEnd)
  {
    while(pBegin < pEnd && (*pBegin & 0x1) != 0)
      pBegin++;

    while(pBegin < pEnd && (*pEnd & 0x1) == 0)
      pEnd--;

    if(pBegin < pEnd)
    {
      int temp = *pBegin;
      *pBegin = *pEnd;
      *pEnd = temp;
    }
  }
}

bool isEven(int n)
{
  return (n & 1) == 0;
}

void ReorderArr(int* pData, unsigned int length, bool (*func)(int))
{
  if(pData == NULL || length <= 0)
    return; 

  int *pBegin = pData;
  int *pEnd = pData + length - 1;
  while(pBegin < pEnd)
  {
    while(pBegin < pEnd && !func(*pBegin))
      pBegin++;

    while(pBegin < pEnd && func(*pEnd))
      pEnd--;

    if(pBegin < pEnd)
    {
      int temp = *pBegin;
      *pBegin = *pEnd;
      *pEnd = temp;
    }
  }
}

void Reorder2(int* pData, unsigned int length)
{
  ReorderArr(pData, length, isEven);
}

///////////////////////////////////////测试代码
void Print(int pData[], int length)
{
  if(length < 0)
    return;
  for(int i = 0; i < length; ++i)
  {
    printf("%d ", pData[i]);
  }
  printf("\n");
}
void Test(const char* testname, int* pData, int length)
{
  printf("%s begins \n", testname);

  int* copy = new int[length];
  for(int i = 0; i < length; ++i)
  {
    copy[i] = pData[i];
  }
  Print(pData, length);
  printf("solution 1 :\n");
  Reorder1(pData, length);
  Print(pData, length);

  Print(copy, length);
  printf("solution 2 :\n");
  Reorder2(copy, length);
  Print(copy, length);

  delete[] copy;
}

void Test1()
{
  int numbers[] = {1, 2, 3, 4, 5, 6, 7};
  Test("Test1", numbers, sizeof(numbers)/sizeof(int));
}

void Test2()
{
  int numbers[] = {2, 4, 6, 1, 3, 5, 7};
  Test("Test2", numbers, sizeof(numbers)/sizeof(int));
}

void Test3()
{
  int numbers[] = {1, 3, 5, 7, 2, 4, 6};
  Test("Test3", numbers, sizeof(numbers)/sizeof(int));
}

void Test4()
{
  int numbers[] = {1};
  Test("Test4", numbers, sizeof(numbers)/sizeof(int));
}

void Test5()
{
  int numbers[] = {2};
  Test("Test5", numbers, sizeof(numbers)/sizeof(int));
}

void Test6()
{
  Test("Test6", NULL, 0);
}


int main()
{
  Test1();
  Test2();
  Test3();
  Test4();
  Test5();
  Test6();
  return 0;
}
