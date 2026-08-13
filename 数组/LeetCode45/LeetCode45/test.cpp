class Solution {
public:
	int jump(vector<int>& nums) {
		int n = nums.size();
		int maxPos = 0, end = 0, step = 0;

		for (int i = 0; i < n - 1; ++i){
			if (maxPos >= i){ // maxPos下标操作，表示每次走过的位置的下标
				maxPos = max(maxPos, i + nums[i]);
				if (i == end){ // end表示上一次maxPos的位置，当i==end时，表示i刚走到上一次maxPos走过的位置，更新end的位置，step+1
					end = maxPos;
					++step;
				}
			}
		}
		return step;
	}
};