#include <iostream>

struct BinaryTreeNode
{
	BinaryTreeNode* left;
	BinaryTreeNode* right;
	int val;

	BinaryTreeNode(int data)
		: left(nullptr)
		, right(nullptr)
		, val(data)
	{}
};

// ====================方法1====================
int TreeDepth(const BinaryTreeNode* pRoot)
{
	if (pRoot == nullptr)
		return 0;

	int nLeft = TreeDepth(pRoot->left);
	int nRight = TreeDepth(pRoot->right);

	return (nLeft > nRight) ? (nLeft + 1) : (nRight + 1);
}

bool IsBalanced_Solution1(const BinaryTreeNode* pRoot)
{
	if (pRoot == nullptr)
		return true;

	int left = TreeDepth(pRoot->left);
	int right = TreeDepth(pRoot->right);
	int diff = left - right;
	if (diff > 1 || diff < -1)
		return false;

	return IsBalanced_Solution1(pRoot->left)
		&& IsBalanced_Solution1(pRoot->right);
}

// ====================方法2====================
bool IsBalanced(const BinaryTreeNode* pRoot, int* pDepth);

bool IsBalanced_Solution2(const BinaryTreeNode* pRoot)
{
	int depth = 0;
	return IsBalanced(pRoot, &depth);
}

bool IsBalanced(const BinaryTreeNode* pRoot, int* pDepth)
{
	if (pRoot == nullptr)
	{
		*pDepth = 0;
		return true;
	}

	int left, right;
	if (IsBalanced(pRoot->left, &left) && IsBalanced(pRoot->right, &right))
	{
		int diff = left - right;
		if (diff >= -1 && diff <= 1)
		{
			*pDepth = 1 + (left > right ? left : right);
			return true;
		}
	}
	return false;
}


// ====================测试代码====================
void Test(const char* testName, const BinaryTreeNode* pRoot, bool expected)
{
	if (testName != nullptr)
		printf("%s begins:\n", testName);

	printf("Solution1 begins: ");
	if (IsBalanced_Solution1(pRoot) == expected)
		printf("Passed.\n");
	else
		printf("Failed.\n");

	printf("Solution2 begins: ");
	if (IsBalanced_Solution2(pRoot) == expected)
		printf("Passed.\n");
	else
		printf("Failed.\n");
}



// 不是完全二叉树，但是平衡二叉树
//             1
//         /      \
//        2        3
//       /\         \
//      4  5         6
//        /
//       7
void Test2()
{
	BinaryTreeNode* pNode1 = new BinaryTreeNode(1);
	BinaryTreeNode* pNode2 = new BinaryTreeNode(2);
	BinaryTreeNode* pNode3 = new BinaryTreeNode(3);
	BinaryTreeNode* pNode4 = new BinaryTreeNode(4);
	BinaryTreeNode* pNode5 = new BinaryTreeNode(5);
	BinaryTreeNode* pNode6 = new BinaryTreeNode(6);
	BinaryTreeNode* pNode7 = new BinaryTreeNode(7);

	pNode1->left = pNode2;
	pNode1->right = pNode3;
	pNode2->left = pNode4;
	pNode2->right = pNode5;
	pNode5->left = pNode7;
	pNode3->right = pNode6;

	Test("Test2", pNode1, true);

}

// 不是平衡二叉树
//             1
//         /      \
//        2        3
//       /\         
//      4  5        
//        /
//       6
void Test3()
{
	BinaryTreeNode* pNode1 = new BinaryTreeNode(1);
	BinaryTreeNode* pNode2 = new BinaryTreeNode(2);
	BinaryTreeNode* pNode3 = new BinaryTreeNode(3);
	BinaryTreeNode* pNode4 = new BinaryTreeNode(4);
	BinaryTreeNode* pNode5 = new BinaryTreeNode(5);
	BinaryTreeNode* pNode6 = new BinaryTreeNode(6);

	pNode1->left = pNode2;
	pNode1->right = pNode3;
	pNode2->left = pNode4;
	pNode2->right = pNode5;
	pNode5->left = pNode6;

	Test("Test3", pNode1, false);

}


//               1
//              /
//             2
//            /
//           3
//          /
//         4
//        /
//       5
void Test4()
{
	BinaryTreeNode* pNode1 = new BinaryTreeNode(1);
	BinaryTreeNode* pNode2 = new BinaryTreeNode(2);
	BinaryTreeNode* pNode3 = new BinaryTreeNode(3);
	BinaryTreeNode* pNode4 = new BinaryTreeNode(4);
	BinaryTreeNode* pNode5 = new BinaryTreeNode(5);

	pNode1->left = pNode2;
	pNode2->left = pNode3;
	pNode3->left = pNode4;
	pNode4->left = pNode5;
	Test("Test4", pNode1, false);
}




int main(int argc, char* argv[])
{
	Test2();
	Test3();
	Test4();

	return 0;
}