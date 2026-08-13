#include <iostream>
#include <vector>


int movingCountCore(int threshold, int rows, int cols, int row, int col, bool* visited);
bool check(int threshold, int rows, int cols, int row, int col, bool* visited);
int getDigitSum(int number);


int RobotMove(int threshold, int rows, int cols)
{
  if(threshold <= 0 || rows <= 0 || cols <= 0)
    return 0;

  bool *visited = new bool[rows*cols];
  for(int i = 0; i < rows *cols; ++i)
    visited[i] = false;
  // 这里机器人从（0,0）开始，所以不用双循环，找入口点
  int count = movingCountCore(threshold, rows, cols, 0, 0, visited);
  delete[] visited;
  return count;
}

int movingCountCore(int threshold, int rows, int cols, int row, int col, bool* visited)
{
  int count = 0;
  if(check(threshold, rows, cols, row, col, visited))
  {
    visited[row*cols + col] = true;
    count = 1 + movingCountCore(threshold, rows, cols, row + 1, col, visited)
      + movingCountCore(threshold, rows, cols, row - 1, col, visited)
      + movingCountCore(threshold, rows, cols, row, col + 1, visited)
      + movingCountCore(threshold, rows, cols, row, col - 1, visited);
  }
  return count;
}

bool check(int threshold, int rows, int cols, int row, int col, bool* visited)
{
  if(row >= 0 && row < rows && col >= 0 && col < cols && (getDigitSum(row) + getDigitSum(col)) <= threshold && !visited[row*cols + col])
  {
    return true;
  }
  return false;
}

int getDigitSum(int number)
{
  int sum = 0;
  while(number > 0)
  {
    sum += number % 10;
    number /= 10;
  }
  return sum;
}
/////////////////////测试代码
void test(const char* testname, int threshold, int rows, int cols, int expected)
{
  if(testname != nullptr)
    std::cout << testname << " ";
  if(RobotMove(threshold, rows, cols) == expected)
  {
    std::cout << "Passed!" << std::endl;
  }
  else 
  {
    std::cout << "Failed!" << std::endl;
  }
}


// 方格多行多列
void test1()
{
  test("Test1", 5, 10, 10, 21);
}

// 方格多行多列
void test2()
{
  test("Test2", 15, 20, 20, 359);
}


// 方格只有一行，机器人能到达所有方格
void test4()
{
  test("Test4", 10, 1, 10, 10);
}


int main()
{
  test1();
  test2();
  test4();
  return 0;
}
