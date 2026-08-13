#include <stdio.h>


struct BinaryTreeNode{
  BinaryTreeNode* pLeft;
  BinaryTreeNode* pRight;
  BinaryTreeNode* pParent;
  int Value;
};

BinaryTreeNode* CreateBinaryNode(int value)
{
  BinaryTreeNode* Node = new BinaryTreeNode();
  Node->pLeft = NULL;
  Node->pRight = NULL;
  Node->pParent = NULL;
  Node->Value = value;
  return Node;
}

void ConnectionNode(BinaryTreeNode* pParent, BinaryTreeNode* left, BinaryTreeNode* right)
{
  if(pParent != NULL)
  {
    pParent->pLeft = left;
    pParent->pRight = right;

    if(left != NULL)
    {
      left->pParent = pParent;
    }
    if(right != NULL)
    {
      right->pParent = pParent;
    }
  }
}

void PrintNode(BinaryTreeNode* root)
{
  if(root != NULL)
  {
    PrintNode(root->pLeft);
    printf("%d ", root->Value);
    PrintNode(root->pRight);
  }
}

void Destory(BinaryTreeNode* root)
{
  if(root != NULL)
  {
    Destory(root->pLeft);
    Destory(root->pRight);
    delete root;
    root = NULL;
  }
}


BinaryTreeNode* GetNextNode(BinaryTreeNode* root)
{
  if(root == NULL)
    return NULL;
  BinaryTreeNode* ret = NULL;
  if(root->pRight != NULL)
  {
    BinaryTreeNode* pCur = root->pRight;
    while(pCur->pLeft != NULL)
      pCur = pCur->pLeft;
    ret = pCur;
  }
  else if(root->pParent != NULL) 
  {
    BinaryTreeNode* parent = root->pParent;
    BinaryTreeNode* cur = root;
    while(parent->pParent != NULL && cur == parent->pRight)
    {
      cur = parent;
      parent = parent->pParent;
    }
    ret = parent;
  }
  return ret;
}

void Test()
{
  BinaryTreeNode* pNode8 = CreateBinaryNode(8);
  BinaryTreeNode* pNode6 = CreateBinaryNode(6);
  BinaryTreeNode* pNode10 = CreateBinaryNode(10);
  BinaryTreeNode* pNode5 = CreateBinaryNode(5);
  BinaryTreeNode* pNode7 = CreateBinaryNode(7);
  BinaryTreeNode* pNode9 = CreateBinaryNode(9);
  BinaryTreeNode* pNode11 = CreateBinaryNode(11);

  ConnectionNode(pNode8, pNode6, pNode10);
  ConnectionNode(pNode6, pNode5, pNode7);
  ConnectionNode(pNode10, pNode9, pNode11);

  PrintNode(pNode8);
  BinaryTreeNode* Node = GetNextNode(pNode5);
  printf("\n%d ", Node->Value);
  Node = GetNextNode(pNode7);
  printf("%d ", Node->Value);
  Node = GetNextNode(pNode10);
  printf("%d\n", Node->Value);
}

int main()
{
  Test();
  return 0;
}

