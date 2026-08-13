#include <stdio.h>
#include <unistd.h>

#include <iostream>
#include <vector>
#include  <map>
#include <string>

// 这里的map相当于是一个二维数组，第一列char类型的，第二列是string类型的
// 利用M访问的时候也是按照二维数组的方式访问
std::map<char, std::string> M{
  {'2', "abc"}, {'3', "def"}, {'4',"ghi"}, {'5', "jkl"}, {'6', "mno"}, {'7', "pqrs"}, {'8', "tuv"}, {'9',"wxyz"}
};

std::vector<std::string> ans;
std::string current;

void DFS(int index, std::string digits)
{
  if(digits.size() == index)
  {
    ans.push_back(current);
    return;
  }
  for(int i = 0; i < M[digits[index]].size(); i++)
  {
    // index : 表示要插入的第几个数字 digits[indx]：digits里的数字 M[digits[index]]:表示对应数字的行， M[digits[index]][i]:所在行的第i个数字
    // 这里都是数字，但是上面的是char，string类型的，所以要分清
    current.push_back(M[digits[index]][i]);
    DFS(index + 1, digits);
    current.pop_back();
  }
}

std::vector<std::string> letterCombinations(std::string digits)
{
  if(digits.size() == 0)
    return ans;
  DFS(0, digits);
  return ans;
}

int main()
{
  std::string s("239");
  std::vector<std::string> ret = letterCombinations(s);
  for(auto e : ret)
  {
    std::cout << e << " ";
  }
  std::cout << std::endl << ans.size() << std::endl;
  return 0;
}
