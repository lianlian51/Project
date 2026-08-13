//#include <iostream>
//#include <fstream>
//
//struct BinaryTreeNode
//{
//	BinaryTreeNode* left;
//	BinaryTreeNode* right;
//	int val;
//
//	BinaryTreeNode(const int& data = 0)
//		: left(nullptr)
//		, right(nullptr)
//		, val(data)
//	{}
//};
//
//typedef BinaryTreeNode Node;
//
//void Serialize(const Node* pRoot, std::ostream& stream)
//{
//	if (pRoot == nullptr)
//	{
//		stream << "$,";
//		return;
//	}
//
//	stream << pRoot->val << ',';
//	Serialize(pRoot->left, stream);
//	Serialize(pRoot->right, stream);
//}
//
//bool ReadStream(std::istream& stream, int* number)
//{
//	if (stream.eof())
//		return false;
//
//	char buffer[32];
//	buffer[0] = '\0';
//	char ch;
//	stream >> ch;
//	int i = 0;
//	while (!stream.eof() && ch != ',')
//	{
//		buffer[i++] = ch;
//		stream >> ch;
//	}
//
//	bool numberic = false;
//	if (i > 0 && buffer[0] != '$')
//	{
//		*number = atoi(buffer);
//		numberic = true;
//	}
//	return numberic;
//}
//
//void Deserialize(Node** pRoot, std::istream& stream)
//{
//	int number;
//	if (ReadStream(stream, &number))
//	{
//		*pRoot = new Node();
//		(*pRoot)->left = nullptr;
//		(*pRoot)->right = nullptr;
//		(*pRoot)->val = number;
//
//		Deserialize(&((*pRoot)->left), stream);
//		Deserialize(&((*pRoot)->right), stream);
//	}
//}
//
//// ==================== Test Code ====================
//bool isSameTree(const BinaryTreeNode* pRoot1, const BinaryTreeNode* pRoot2)
//{
//	if (pRoot1 == nullptr && pRoot2 == nullptr)
//		return true;
//
//	if (pRoot1 == nullptr || pRoot2 == nullptr)
//		return false;
//
//	if (pRoot1->val != pRoot2->val)
//		return false;
//
//	return isSameTree(pRoot1->left, pRoot2->left) &&
//		isSameTree(pRoot1->right, pRoot2->right);
//}
//
//void PreOrder(const Node* pRoot)
//{
//	if (pRoot)
//	{
//		std::cout << pRoot->val << " ";
//		PreOrder(pRoot->left);
//		PreOrder(pRoot->right);
//	}
//}
//
//void Test(const char* testname, const Node* pRoot)
//{
//	std::cout << testname << " begins: ";
//	PreOrder(pRoot);
//	std::cout << std::endl;
//	char* filename = "test.txt";
//	std::ofstream fileout;
//	fileout.open(filename);
//	Serialize(pRoot, fileout);
//	fileout.close();
//	// 打印序列化
//	std::ifstream filein;
//	filein.open(filename);
//	char ch;
//	while (!filein.eof())
//	{
//		filein >> ch;
//		std::cout << ch;
//	}
//	filein.close();
//	std::cout << std::endl;
//
//	// 反序列化测试
//	
//	std::ifstream stream;
//	stream.open(filename);
//	Node* newRoot = nullptr;
//	Deserialize(&newRoot, stream);
//	stream.close();
//
//	PreOrder(newRoot);
//	std::cout << std::endl;
//
//	if (isSameTree(pRoot, newRoot))
//		std::cout << "same" << std::endl;
//	else
//		std::cout << "not same" << std::endl;
//}
//
//Node* Test1()
//{
//	BinaryTreeNode* node8 = new Node(8);
//	BinaryTreeNode* node6 = new Node(6);
//	BinaryTreeNode* node10 = new Node(10);
//	BinaryTreeNode* node5 = new Node(5);
//	BinaryTreeNode* node7 = new Node(7);
//	BinaryTreeNode* node9 = new Node(9);
//	BinaryTreeNode* node11 = new Node(11);
//
//	node8->left = node6;
//	node8->right = node10;
//	node6->left = node5;
//	node6->right = node7;
//	node10->left = node9;
//	node10->right = node11;
//	return node8;
//}
//
//Node* Test2()
//{
//	BinaryTreeNode* node5 = new Node(5);
//	BinaryTreeNode* node4 = new Node(4);
//	BinaryTreeNode* node3 = new Node(3);
//	BinaryTreeNode* node2 = new Node(2);
//
//
//	node5->left = node4;
//	node4->left = node3;
//	node3->left = node2;
//
//	return node5;
//}
//
//
//
//int main()
//{
//	Node* p = Test1();
//	Test("Test1", p);
//	
//	p = Test2();
//	Test("Test2", p);
//
//
//	return 0;
//}

#include <string_view>
#include <string>
#include <iostream>

int main()
{
	return 0;
}