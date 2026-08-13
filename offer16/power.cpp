#include <iostream>

bool g_InvalidInput = false;
bool equal(double num1, double num2);
double PowerWithUnsignedExponent(double base, unsigned int exponent);


double Power(double base, double exponent)
{
  g_InvalidInput = false;
  if(equal(base, 0.0) && exponent < 0)
  {
    g_InvalidInput = true;
    return 0;
  }
  // 处理exponent负数的情况
  unsigned int absExponent = (unsigned int)exponent;
  if(exponent < 0)
    absExponent = (unsigned int)(-exponent);

  double result = PowerWithUnsignedExponent(base, absExponent);
  if(exponent < 0)
    result = 1.0 / result;
  return result;
}

bool equal(double num1, double num2)
{
  if(num1 - num2 < 0.0000001 && num1 - num2 > -0.0000001)
    return true;
  else 
    return false;
}


double PowerWithUnsignedExponent(double base, unsigned int exponent)
{
  if(exponent == 0)
    return 1;
  if(exponent == 1)
    return base;

  double result = PowerWithUnsignedExponent(base, exponent >> 1);
  result *= result;
  if((exponent & 0x1) == 1)
    result *= base;
  return result;
}


//////////////////////////////////////测试代码
void Test(const char* testname, double base, int exponent, double resExponent, bool ExpectedFlag)
{
  std::cout << testname << " ";
  double result = Power(base, exponent);
  if(resExponent == result && ExpectedFlag == g_InvalidInput)
  {
    std::cout << "Passed!" << std::endl;
  }
  else 
  {
    std::cout << "Failed!" << std::endl;
  }
}

int main()
{
  // 底数、指数都为正数
  Test("Test1", 2, 3, 8, false);

  // 底数为负数、指数为正数
  Test("Test2", -2, 3, -8, false);

  // 指数为负数
  Test("Test3", 2, -3, 0.125, false);

  // 指数为0
  Test("Test6", 0, 4, 0, false);

  // 底数为0、指数为负数
  Test("Test7", 0, -4, 0, true);

  return 0;

}

