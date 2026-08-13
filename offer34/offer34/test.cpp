#include <iostream>
#include <vector>

struct BinaryTreeNode
{
	BinaryTreeNode(const int data)
	:left(nullptr)
	, right(nullptr)
	, val(data)
	{}

	BinaryTreeNode* left;
	BinaryTreeNode* right;
	int val;
};

typedef BinaryTreeNode Node;

void FindPath(Node* pRoot, std::vector<int>& path, int expected, int current);

void FindPath(Node* pRoot, int expected)
{
	if (pRoot == nullptr)
		return;

	std::vector<int> path;
	int current = 0;
	FindPath(pRoot, path, expected, current);
}

void FindPath(Node* pRoot, std::vector<int>& path, int expected, int current)
{
	current += pRoot->val;
	path.push_back(pRoot->val);
	if (pRoot->left == nullptr && pRoot->right == nullptr)
	{
		if (expected == current)
		{
			std::cout << "a path :";
			for (int i = 0; i < path.size(); ++i)
			{
				std::cout << path[i] << " ";
			}
			std::cout << std::endl;
		}
	}

	if (pRoot->left)
		FindPath(pRoot->left, path, expected, current);
	if (pRoot->right)
		FindPath(pRoot->right, path, expected, current);

	path.pop_back();
	//current -= pRoot->val;
}

Node* Create1()
{
	Node* node4 = new Node(4);
	Node* node5 = new Node(5);
	Node* node7 = new Node(7);
	Node* node10 = new Node(10);
	Node* node12 = new Node(12);

	node10->left = node5;
	node10->right = node12;
	node5->left = node4;
	node5->right = node7;
	return node10;
}


Node* Create2()
{
	Node* node1 = new Node(1);
	Node* node2 = new Node(2);
	Node* node3 = new Node(3);
	Node* node4 = new Node(4);
	Node* node5 = new Node(5);

	node1->left = node2;
	node2->left = node3;
	node3->left = node4;
	node4->left = node5;
	return node1;
}


int main()
{
	Node* p = Create1();
	FindPath(p, 22);
	// FindPath(p, 15);
	//FindPath(p, 16);
	return 0;
}