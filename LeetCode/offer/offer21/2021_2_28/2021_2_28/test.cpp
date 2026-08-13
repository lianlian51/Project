/**
* Note: The returned array must be malloced, assume caller calls free().
*/
int* exchange(int* nums, int numsSize, int* returnSize){
	int left = 0;
	int right = numsSize - 1;

	while (left < right)
	{
		if ((nums[left] % 2) == 1)
		{
			left++;
			continue;
		}

		if ((nums[right] % 2) == 0)
		{
			right--;
			continue;
		}

		if ((nums[left] % 2 == 0) && (nums[right] % 2) == 1)
		{
			int temp = nums[left];
			nums[left] = nums[right];
			nums[right] = temp;

			left++;
			right--;
		}
	}
	*returnSize = numsSize;
	return nums;
}