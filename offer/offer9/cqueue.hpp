#pragma once 
#include <stack>

template<class T>
class CQueue
{
public:
  CQueue()
  {}

  ~CQueue()
  {}

  void AppendTail(const T& value);

  T deleteHead();
  

  private:
    std::stack<T> st1;
    std::stack<T> st2;
};

template<class T>
void CQueue<T>::AppendTail(const T& value)
{
  st1.push(value);
}

template<class T>
T CQueue<T>::deleteHead()
{
  if(st2.empty())
  {
    while(!st1.empty())
    {
      T& top = st1.top();
      st1.pop();
      st2.push(top);
    }
  }

  T head = st2.top();
  st2.pop();
  return head;
}
