#include <stdio.h>
#include <string.h>

// 赋值运算符
class CMyString{
  public:
    CMyString();
    CMyString(char* str = NULL);
    CMyString& operator=(const CMyString& str);
    ~CMyString();
  private:
    char* m_pData;
};
// 经典写法
CMyString& CMyString::operator=(const CMyString& str)
{
  // 判断是不是给自己赋值
  if(this == &str)
    return *this;
  // 释放掉实例化自身已有的内存
  delete[] m_pData;
  m_pData = NULL;

  // new开辟空间失败怎么办？
  m_pData = new char[strlen(str.m_pData) + 1];
  strcpy(m_pData, str.m_pData);
  return *this;
}
// 高级程序员写法:创建一个临时对象，交换strTemp.m_pData和自身实例化的m_pData,
// strTemp局部变量，出了作用域就会调用析构函数
CMyString& CMyString::operator=(const CMyString& str)
{
  if(this != &str)
  {
    CMyString strTemp(str);

    char* pTemp = strTemp.m_pData;
    strTemp.m_pData = m_pData;
    m_pData = pTemp;
  }
  return *this;
}

int main()
{
  return 0;
}
