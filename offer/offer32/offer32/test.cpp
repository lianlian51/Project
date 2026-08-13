#include <iostream>
#include <queue>
#include <deque>
#include <stack>

struct BinaryTreeNode
{
	int m_val;
	BinaryTreeNode* m_pLeft;
	BinaryTreeNode* m_pRight;

	BinaryTreeNode(int data = 0)
		: m_val(data)
		, m_pLeft(nullptr)
		, m_pRight(nullptr)
	{}
};

typedef BinaryTreeNode Node;

// 从头到尾打印二叉树
void Print(Node* pRoot)
{
	if (pRoot == nullptr)
		return;
	std::deque<Node*> dp;
	dp.push_back(pRoot);
	while (!dp.empty())
	{
		Node* node = dp.front();
		dp.pop_front();
		std::cout << node->m_val << " ";

		if (node->m_pLeft)
			dp.push_back(node->m_pLeft);

		if (node->m_pRight)
			dp.push_back(node->m_pRight);
	}
}

// 一行一行的打印二叉树
void PrintLines(Node* pRoot)
{
	if (pRoot == nullptr)
		return;
	std::queue<Node*> q;
	q.push(pRoot);
	while (!q.empty())
	{
		Node* node;
		int size = q.size();
		for (int i = 0; i < size; ++i)
		{
			node = q.front();
			std::cout << node->m_val << " ";
			q.pop();
			if (node->m_pLeft)
				q.push(node->m_pLeft);
			if (node->m_pRight)
				q.push(node->m_pRight);
		}
		std::cout << std::endl;
	}
}

void _PrintLines(Node* pRoot)
{
	if (pRoot == nullptr)
		return;
	std::queue<Node*> q;
	q.push(pRoot);
	int tobePrint = 1;
	int nextLine = 0;
	while (!q.empty())
	{
		Node* node = q.front();
		q.pop();
		std::cout << node->m_val << " ";
		if (node->m_pLeft)
		{
			q.push(node->m_pLeft);
			++nextLine;
		}

		if (node->m_pRight)
		{
			q.push(node->m_pRight);
			++nextLine;
		}

		--tobePrint;
		if (tobePrint == 0)
		{
			std::cout << std::endl;
			tobePrint = nextLine;
			nextLine = 0;
		}
	}
}

// 之字打印二叉树
void PrintZ(Node* pRoot)
{
	if (pRoot == nullptr)
		return;
	std::stack<Node*> line[2];
	int current = 0;
	int next = 1;
	line[current].push(pRoot);
	while (!line[0].empty() || !line[1].empty())
	{
		Node* node = line[current].top();
		line[current].pop();
		std::cout << node->m_val << " ";
		if (current == 0)
		{
			if (node->m_pLeft)
				line[next].push(node->m_pLeft);
			if (node->m_pRight)
				line[next].push(node->m_pRight);
		}
		else
		{
			if (node->m_pRight)
				line[next].push(node->m_pRight);
			if (node->m_pLeft)
				line[next].push(node->m_pLeft);
		}

		if (line[current].empty())
		{
			std::cout << std::endl;
			current = 1 - current;
			next = 1 - next;
		}
	}
}

Node* Create1()
{
	Node* node5 = new Node(5);
	Node* node6 = new Node(6);
	Node* node7 = new Node(7);
	Node* node8 = new Node(8);
	Node* node9 = new Node(9); 
	Node* node10 = new Node(10);
	Node* node11 = new Node(11);

	node8->m_pLeft = node6;
	node8->m_pRight = node10;
	node6->m_pLeft = node5;
	node6->m_pRight = node7;
	node10->m_pLeft = node9;
	node10->m_pRight = node11;
	return node8;
}

Node* Create2()
{
	Node* node5 = new Node(5);
	Node* node6 = new Node(6);
	Node* node7 = new Node(7);
	Node* node8 = new Node(8);

	node5->m_pRight = node6;
	node6->m_pRight = node7;
	node7->m_pRight = node8;

	return node5;
}

int main()
{
	Node* p = Create2();
	std::cout << "一行打印：" << std::endl;
	Print(p);
	std::cout << std::endl;

	std::cout << "按层打印：" << std::endl;
	PrintLines(p);
	std::cout << std::endl;

	std::cout << "按层打印2：" << std::endl;
	_PrintLines(p);
	std::cout << std::endl;

	std::cout << "Z字打印：" << std::endl;
	PrintZ(p);
	std::cout << std::endl;
	return 0;
}