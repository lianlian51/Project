#include <iostream>
#include <vector>
#include <string>


bool hasPathCore(std::vector<std::vector<char>> vec, int rows, int cols, int row, int col, std::string str, int lengthPath, std::vector<std::vector<bool>> visited);

bool HasPath(std::vector<std::vector<char>> vec, std::string str)
{
  int rows = vec.size();
  int cols = vec[0].size();

  int lengthPath = 0;
  std::vector<std::vector<bool>> visited(rows, std::vector<bool> (cols, true));
  for(int row = 0; row < rows; ++row)
  {
    for(int col = 0; col < cols; ++col)
    {
      bool flag = hasPathCore(vec, rows, cols, row, col, str, lengthPath, visited);
      if(flag)
        return true;
    }
  }

  return false;
}

bool hasPathCore(std::vector<std::vector<char>> vec, int rows, int cols, int row, int col, std::string str, int lengthPath, std::vector<std::vector<bool>> visited)
{
  if(str[lengthPath] == '\0')
    return true;
  bool rethasPath = false;
  if(row >= 0 && row < rows && col >= 0 && col < cols && vec[row][col] == str[lengthPath] && visited[row][col])
  {
    ++lengthPath;
    visited[row][col] = false;
    rethasPath = hasPathCore(vec, rows, cols, row, col - 1, str, lengthPath, visited) 
    || hasPathCore(vec, rows, cols, row, col + 1, str, lengthPath, visited) 
    || hasPathCore(vec, rows, cols, row - 1, col, str, lengthPath, visited) 
    || hasPathCore(vec, rows, cols, row + 1, col, str, lengthPath, visited);

    if(!rethasPath){
      --lengthPath;
      visited[row][col] = true;
    }
  }
  return rethasPath;
}

int main()
{
  std::vector<std::vector<char>> vec{{'A', 'B', 'C', 'E'}, {'S', 'F', 'C', 'S'}, {'A', 'D', 'E', 'E'}};
  std::cout << HasPath(vec, "SEE") << std::endl;
  std::cout << HasPath(vec, "ABFD") << std::endl;
  std::cout << HasPath(vec, "CDEF") << std::endl;;
  return 0;
}
