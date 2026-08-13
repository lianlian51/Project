#include <iostream>

void PrintNumber(int number)
{
	std::cout << number << "\t";
}

void PrintMatrix(int** matrix, int rows, int cols);
void PrintMatrix(int** matrix, int rows, int cols, int start);


void PrintMatrix(int** matrix, int rows, int cols)
{
	if (matrix == nullptr || rows <= 0 || cols <= 0)
		return;
	int start = 0;
	while (rows > 2 * start && cols > 2 * start)
	{

		PrintMatrix(matrix, rows, cols, start);
		++start;
	}
}

void PrintMatrix(int** matrix, int rows, int cols, int start)
{
	int endX = rows - 1 - start;
	int endY = cols - 1 - start;

	// 打印从左到右一行
	for (int i = start; i <= endY; ++i)
	{
		PrintNumber(matrix[start][i]);
	}

	// 打印从上到下一行
	if (start < endX)
	{
		for (int i = start + 1; i <= endX; ++i)
		{
			PrintNumber(matrix[i][endY]);
		}
	}


	// 打印从右到左一行
	if (start < endX && start < endY)
	{
		for (int i = endY - 1; i >= start; --i)
		{
			PrintNumber(matrix[endX][i]);
		}
	}

	// 打印从下到上一行
	if (start < endX - 1 && start < endY)
	{
		for (int i = endX - 1; i >= start + 1; --i)
		{
			PrintNumber(matrix[i][start]);
		}
	}
}

// ====================测试代码====================
void Test(int cols, int rows)
{
	printf("Test Begin: %d columns, %d rows.\n", rows, cols);

	if (cols < 1 || rows < 1)
		return;

	int** numbers = new int*[cols];
	for (int i = 0; i < cols; ++i)
	{
		numbers[i] = new int[rows];
		for (int j = 0; j < rows; ++j)
		{
			numbers[i][j] = i * rows + j + 1;
		}
	}

	PrintMatrix(numbers, cols, rows);
	printf("\n");

	for (int i = 0; i < cols; ++i)
		delete[](int*)numbers[i];

	delete[] numbers;
}


int main()
{
	Test(1, 1);
	Test(4, 4); 
	Test(5, 2);
	Test(2, 5);
	return 0;
}