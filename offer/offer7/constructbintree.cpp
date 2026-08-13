#include <cstdio>
#include <exception>
#include <iostream>

struct BinaryTreeNode{
  int m_nValue;
  BinaryTreeNode* m_pLeft;
  BinaryTreeNode* m_pRight;
};

BinaryTreeNode* ConstructCore(int* startPreorder, int* endPreorder, int* startInorder, int* endInorder);

BinaryTreeNode* Construct(int* preorder, int* inorder, int length)
{
  if(preorder == NULL || inorder == NULL || length <= 0)
    return NULL;
  return ConstructCore(preorder, preorder + length - 1, inorder, inorder + length - 1);
}

BinaryTreeNode* ConstructCore(int* startPreorder, int* endPreorder, int* startInorder, int* endInorder)
{
  int rootValue = startPreorder[0];
  BinaryTreeNode* root = new BinaryTreeNode();
  root->m_nValue = rootValue;
  root->m_pLeft = root->m_pRight = NULL;

  if(startPreorder == endPreorder)
  {
    if(startPreorder == endPreorder && *startPreorder == * startInorder)
      return root;
    else 
      throw std::exception("Invalid input.");
  }

  int* rootInorder = startInorder;
  while(rootInorder <= endInorder && *rootInorder != rootValue)
    ++rootInorder;
  if(rootInorder == endInorder && *rootInorder != rootValue)
    throw std::exception("Invalid input!");

  int leftLength = rootInorder - startInorder;
  int* leftLengthend = startPreorder + leftLength;

  if(leftLength > 0){
    root->m_pLeft = ConstructCore(startPreorder + 1, leftLengthend, startInorder, rootInorder - 1);
  }
  if(leftLength < endPreorder - startPreorder){
    root->m_pRight = ConstructCore(startPreorder + leftLength + 1, endPreorder, rootInorder + 1, endInorder);
  }
}


void Test(char* testname, int* preorder, int* inorder, int length)
{
  if(testname != nullptr)
    printf("%s begins: ", testname);

  printf("The preorder sequence is: ");
  for(int i = 0; i < length; ++ i)
    printf("%d ", preorder[i]);
  printf("\n");

  printf("The inorder sequence is: ");
  for(int i = 0; i < length; ++ i)
    printf("%d ", inorder[i]);
  printf("\n");

  try{
    BinaryTreeNode* root = Construct(preorder, inorder, length);
    Print(root);
    Destory(root);
  }
  catch(std::exception& exception){
     printf("Invalid input.\n");
  }
}


int main()
{
  return 0;
}

