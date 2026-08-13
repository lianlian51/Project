#include <stdio.h>


bool matchCore(const char* str, const char* pattern);
bool match(const char* str, const char* pattern)
{
  if(str == NULL|| pattern == NULL) 
    return false;

  return matchCore(str, pattern);
}

bool matchCore(const char* str, const char* pattern)
{
  if(*str == '\0' && *pattern == '\0')
    return true;
  if(*str != '\0' && *pattern == '\0')
    return false;

  if(*(pattern + 1) != '*')
  {
    if(*pattern == *str || (*pattern != *str && *pattern == '.'))
    {
      return matchCore(str + 1, pattern + 1);
    }
  }
  else 
  {
    if(*pattern == *str || (*str != '\0' && *pattern == '.'))
    {
      return matchCore(str, pattern + 2) 
        || matchCore(str + 1, pattern + 2)
        || matchCore(str + 1, pattern);
    }
    else 
      return matchCore(str, pattern + 2);
  }

  return false;
}

// ====================测试代码====================
void Test(const char* testName, const char* str, const char* pattern, bool expected)
{
  if(testName != NULL)
    printf("%s begins: ", testName);

  if(match(str, pattern) == expected)
    printf("Passed.\n");
  else
    printf("FAILED.\n");
}

int main()
{
  Test("Test24", "aaa", "ab*a*c*a", true);
  Test("Test29", "bbbba", ".*a*a", true);
  Test("Test19", "aaa", "a.a", true);
  Test("Test10", "a", "ab*a", false);
  return 0;
}
