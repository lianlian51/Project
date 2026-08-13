class Solution {
public:
	void sortColors(vector<int>& nums) {
		int n0 = 0;
		int n1 = 0;
		int n2 = 0;
		for (int i = 0; i < nums.size(); ++i)
		{
			if (nums[i] == 0)
				n0++;
			else if (nums[i] == 1)
				n1++;
			else if (nums[i] == 2)
				n2++;
		}

		int i = 0;
		while (n0--)
			nums[i++] = 0;

		while (n1--)
			nums[i++] = 1;
		while (n2--)
			nums[i++] = 2;
	}
};