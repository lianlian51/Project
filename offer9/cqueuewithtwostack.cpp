#include "cqueue.hpp"
#include <cstdio>


void Test(char actual, char expected)
{

  if(actual == expected)
  {
    printf("Passed!\n");
  }
  else 
  {
    printf("Failed\n");
  }
}
int main()
{
  CQueue<char> cq;
  cq.AppendTail('a');
  cq.AppendTail('b');
  cq.AppendTail('c');

  char head = cq.deleteHead();
  Test(head, 'a');

  cq.AppendTail('d');
  head = cq.deleteHead();
  Test(head, 'b');

  return 0;
}
