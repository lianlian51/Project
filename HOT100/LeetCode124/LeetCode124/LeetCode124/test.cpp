///**
//* Definition for a binary tree node.
//* struct TreeNode {
//*     int val;
//*     TreeNode *left;
//*     TreeNode *right;
//*     TreeNode() : val(0), left(nullptr), right(nullptr) {}
//*     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
//*     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
//* };
//*/
//class Solution {
//	int sum = INT_MIN;
//public:
//	int maxvalue(TreeNode* root)
//	{
//		if (root == nullptr)
//			return 0;
//
//		// 算出左右子树的价值
//		int left = max(maxvalue(root->left), 0);
//		int right = max(maxvalue(root->right), 0);
//
//		// 算出最大价值
//		int price = left + right + root->val;
//
//		// 更新价值
//		sum = max(sum, price);
//
//		return root->val + max(left, right);
//	}
//
//	int maxPathSum(TreeNode* root) {
//		maxvalue(root);
//		return sum;
//	}
//};

//#include <iostream>
//#include <string.h>
//
//bool Increment(char* number);
//void PrintNumber(char* arr);
//
//void Print1ToMax1(int n)
//{
//	if (n <= 0)
//		return;
//	char* arr = new char[n + 1];
//	memset(arr, '0', n);
//	arr[n] = '\0';
//
//	while (!Increment(arr))
//	{
//		PrintNumber(arr);
//	}
//
//	delete[] arr;
//}
//bool Increment(char* number)
//{
//	bool flag = false;
//	int length = strlen(number);
//	int nTakeOver = 0;
//	for (int i = length - 1; i >= 0; --i)
//	{
//		// 得出末尾数字
//		int nSum = number[i] - '0' + nTakeOver;
//		// 只对末尾数字++
//		if (length - 1 == i)
//			nSum++;
//
//		// 如果i位置数字大于10,则对其进行进位操作
//		if (nSum >= 10)
//		{
//			// 如果访问到0位置元素，则表示溢出
//			if (i == 0)
//			{
//				flag = true;
//			}
//			else
//			{
//				nSum -= 10;
//				nTakeOver = 1;
//				number[i] = nSum + '0';
//			}
//		}
//		else
//		{
//			number[i] = nSum + '0';
//			break;
//		}
//	}
//	return flag;
//}
//void PrintNumber(char* arr)
//{
//	// 将字符数组的第一个非0的数字开始打印
//	int length = strlen(arr);
//	bool isbegin = true;
//	for (int i = 0; i < length; ++i)
//	{
//		// 判断是不是非0
//		if (isbegin && arr[i] != '0')
//			isbegin = false;
//
//		// 打印非0之后的数字
//		if (!isbegin)
//		{
//			printf("%c", arr[i]);
//		}
//	}
//	printf("\t");
//}
//void PrintRecur(char*number, int n, int index);
//void Print1ToMax2(int n)
//{
//	if (n <= 0)
//		return;
//
//	char* number = new char[n + 1];
//	number[n] = '\0';
//
//	for (int i = 0; i < 10; ++i)
//	{
//		number[0] = i + '0';
//		PrintRecur(number, n, 0);
//	}
//	delete[] number;
//}
//void PrintRecur(char*number, int n, int index)
//{
//	if (index == n - 1)
//	{
//		PrintNumber(number);
//		return;
//	}
//
//	for (int i = 0; i < 10; ++i)
//	{
//		number[index + 1] = i + '0';
//		PrintRecur(number, n, index + 1);
//	}
//}
//
//void Test(int n)
//{
//	printf("Test %d begins:\n", n);
//	Print1ToMax1(n);
//	Print1ToMax2(n);
//	printf("Test %d end\n", n);
//}
//
//int main()
//{
//	Test(1);
//	Test(2);
//	Test(-1);
//	return 0;
//}


#include <iostream>
#include <mutex>
#include <thread>
using namespace std;
// 饿汉模式
/*
class Singleton
{
public:
static Singleton* GetInstance()
{
return &m_instance;
}

private:
Singleton(){};

Singleton(Singleton const&) = delete;
Singleton& operator=(Singleton const&) = delete;

static Singleton m_instance;
};

Singleton Singleton::m_instance;
*/

// 懒汉模式
class Singleton
{
public:
	static Singleton* GetInstance()
	{
		if (nullptr == m_pInstance)
		{
			m_mtx.lock();
			if (nullptr == m_pInstance)
			{
				m_pInstance = new Singleton();
			}
			m_mtx.unlock();
		}
		return m_pInstance;
	}

	// 实现一个内嵌垃圾回收类
	class CGarbo
	{
	public:
		~CGarbo()
		{
			if (Singleton::m_pInstance)
				delete Singleton::m_pInstance;
		}
	};

	// 定义一个静态成员变量，程序结束时，系统会自动调用它的析构桉树释放单例对象
	static CGarbo Garbo;

private:
	// 构造函数私有
	Singleton(){};
	// 防拷贝
	Singleton(Singleton const&);
	Singleton& operator=(Singleton const&);

	static Singleton* m_pInstance; // 单例对象指针
	static mutex m_mtx;
};

Singleton* Singleton::m_pInstance = nullptr;
Singleton::CGarbo Garbo;
mutex Singleton::m_mtx;

void func(int n)
{
	cout << Singleton::GetInstance() << endl;
}

int main()
{
	thread t1(func, 10);
	thread t2(func, 10);
	t1.join();
	t2.join();

	cout << Singleton::GetInstance() << endl;
	cout << Singleton::GetInstance() << endl;
}
