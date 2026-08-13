#include <cstdio>


// 递归
long long int fib(int n)
{
  if(n == 0)
    return 0;
  else if(n == 1)
    return 1;
  return fib(n - 1) + fib(n- 2);
}
// 非递归
long long int fib2(int n)
{
  if(n == 0)
    return 0;
  else if(n == 1)
    return 1;
  long long int first = 0;
  long long int second = 1;
  long long int f = 0;
  for(int i = 2; i <= n; ++i)
  {
    f = first + second;
    first = second;
    second = f;
  }
  return f;
}

int main()
{
  printf("%lld %lld\n", fib(1), fib2(1));
  printf("%lld %lld\n", fib(5), fib2(5));
  printf("%lld %lld\n", fib(9), fib2(9));

  return 0;
}
