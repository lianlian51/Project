#include <iostream>
#include <vector>
#include <algorithm>

int maxcutting1(int length)
{
  if(length < 2)
    return 0;
  if(length == 2)
    return 1;
  if(length == 3)
    return 2;

  int* products = new int[length + 1];
  products[0] = 0;
  products[1] = 1;
  products[2] = 2;
  products[3] = 3;

  for(int i = 4; i < length + 1; ++i)
  {
    int max = 0;
    for(int j = 1; j <= i / 2; ++j)
    {
      int temp = products[j]*products[i-j];
      if(temp > max)
        max = temp;
    }
    products[i] = max;
  }
  return products[length];
}

int maxcutting2(int length)
{
  if(length < 2)
    return 0;
  if(length == 2)
    return 1;
  if(length == 3)
    return 2;

  int timesOf3 = length / 3;
  if(length - timesOf3 * 3 == 1)
    timesOf3--;
  int timesOf2 = (length - timesOf3 * 3) / 2;
  return (int)pow(3, timesOf3)*(int)pow(2, timesOf2);
}


int main()
{
  std::cout << maxcutting1(2) << " " << maxcutting2(2) << std::endl;
  std::cout << maxcutting1(5) << " " << maxcutting2(5) << std::endl;
  std::cout << maxcutting1(8) << " " << maxcutting2(8) << std::endl;
  std::cout << maxcutting1(10) << " " << maxcutting2(10) << std::endl;
  return 0;
}
