#include <iostream>

int numberOfBinary1(int number)
{
  int count = 0;
  unsigned int flag = 1;
  while(flag)
  {
    if(number & flag)
      count++;
    flag = flag << 1;
  }
  return count;
}


int numberOfBinary2(int number)
{
  int count = 0;
  while(number)
  {
    ++count;
    number = (number - 1) & number;
  }
  return count;
}


int main()
{
  std::cout << numberOfBinary1(0) << " " << numberOfBinary2(0) << std::endl;
  std::cout << numberOfBinary1(1) << " " << numberOfBinary2(1) << std::endl;
  std::cout << numberOfBinary1(9) << " " << numberOfBinary2(9) << std::endl;
  std::cout << numberOfBinary1(0x7FFFFFFF) << " " << numberOfBinary2(0x7FFFFFFF) << std::endl;
  std::cout << numberOfBinary1(0xFFFFFFFF) << " " << numberOfBinary2(0xFFFFFFFF) << std::endl;
  std::cout << numberOfBinary1(0x80000000) << " " << numberOfBinary2(0x80000000) << std::endl;
  return 0;
}
