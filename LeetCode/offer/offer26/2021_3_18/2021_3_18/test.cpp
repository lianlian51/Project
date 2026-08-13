/**
* Definition for a binary tree node.
* struct TreeNode {
*     int val;
*     struct TreeNode *left;
*     struct TreeNode *right;
* };
*/


bool isAincludeB(struct TreeNode* A, struct TreeNode* B){
	if (B == NULL)
		return true;

	if (A == NULL)
		return false;

	if (A->val != B->val)
		return false;

	return isAincludeB(A->left, B->left) && isAincludeB(A->right, B->right);

}


bool isSubStructure(struct TreeNode *A, struct TreeNode *B)
{
	bool res = false;
	if (A != NULL && B != NULL)
	{
		if (A->val == B->val) res = isAincludeB(A, B);
		if (!res) res = isSubStructure(A->left, B);
		if (!res) res = isSubStructure(A->right, B);
	}
	return res;
}