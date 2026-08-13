/**
* Definition for a binary tree node.
* struct TreeNode {
*     int val;
*     struct TreeNode *left;
*     struct TreeNode *right;
* };
*/


struct TreeNode* buildTree(int* preorder, int preorderSize, int* inorder, int inorderSize){
	if (preorderSize == 0)
		return NULL;
	struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
	node->val = preorder[0];
	int k = 0;
	for (k = 0; k < inorderSize; ++k)
	{
		if (inorder[k] == preorder[0])
			break;
	}
	node->left = buildTree(&preorder[1], k, &inorder[0], k);
	node->right = buildTree(&preorder[k + 1], preorderSize - 1 - k, &inorder[k + 1], inorderSize - 1 - k);
	return node;
}