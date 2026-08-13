#include <iostream>
#include <queue>
#include <vector>
#include <functional>

template<typename T> class DynamicArray
{
public:
	void Insert(T num)
	{
		if ((maxHeap.size() + minHeap.size()) & 1 == 1)
		{
			if (minHeap.size() > 0 && num > minHeap.top())
			{
				minHeap.push(num);
				num = minHeap.top();
				minHeap.pop();
			}
			maxHeap.push(num);
		}
		else
		{
			if (maxHeap.size() > 0 && num < maxHeap.top())
			{
				maxHeap.push(num);
				num = maxHeap.top();
				maxHeap.pop();
			}
			minHeap.push(num);
		}
	}

	T GetMedian()
	{
		int size = maxHeap.size() + minHeap.size();
		if (size == 0)
			throw std::exception("no numbers!");
		T medium = 0;
		if (size & 1 == 1)
			medium = min.top()*1.0;
		else
			medium = (minHeap.top() + maxHeap.top())*1.0 / 2;
		
		return medium;
	}
private:
	std::priority_queue<int, std::vector<int>, std::less<int>> maxHeap;
	std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap;
};


// ====================²âÊÔ´úÂë====================
void Test(char* testName, DynamicArray<double>& numbers, double expected)
{
	if (testName != nullptr)
		printf("%s begins: ", testName);

	if (abs(numbers.GetMedian() - expected) < 0.0000001)
		printf("Passed.\n");
	else
		printf("FAILED.\n");
}

int main(int argc, char* argv[])
{
	DynamicArray<double> numbers;

	printf("Test1 begins: ");
	try
	{
		numbers.GetMedian();
		printf("FAILED.\n");
	}
	catch (const std::exception&)
	{
		printf("Passed.\n");
	}

	numbers.Insert(5);
	Test("Test2", numbers, 5);

	numbers.Insert(2);
	Test("Test3", numbers, 3.5);

	numbers.Insert(3);
	Test("Test4", numbers, 3);

	numbers.Insert(4);
	Test("Test6", numbers, 3.5);

	numbers.Insert(1);
	Test("Test5", numbers, 3);

	numbers.Insert(6);
	Test("Test7", numbers, 3.5);

	numbers.Insert(7);
	Test("Test8", numbers, 4);

	numbers.Insert(0);
	Test("Test9", numbers, 3.5);

	numbers.Insert(8);
	Test("Test10", numbers, 4);

	return 0;
}