class Solution {
public:
	vector<vector<int>> generateMatrix(int n) {
		vector<int> vec;
		for (int i = 1; i <= n*n; ++i){
			vec.push_back(i);
		}
		int k = 0;
		vector<vector<int>> ret(n, vector<int>(n));
		int left = 0, right = n - 1;
		int top = 0, bottom = n - 1;
		while (left <= right && top <= bottom)
		{
			for (int i = left; i <= right; ++i){
				ret[top][i] = vec[k++];
			}
			top++;
			for (int i = top; i <= bottom; ++i){
				ret[i][right] = vec[k++];
			}
			right--;
			if (left < right && top < bottom){
				for (int i = right; i >= left; --i){
					ret[bottom][i] = vec[k++];
				}
				bottom--;
				for (int i = bottom; i >= top; --i){
					ret[i][left] = vec[k++];
				}
				left++;
			}
		}
		return ret;
	}
};