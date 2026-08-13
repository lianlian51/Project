//class Solution {
//public:
//	double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
//		int m = nums1.size();
//		int n = nums2.size();
//
//		vector<int> temp;
//		int i = 0, j = 0;
//		while (i < m && j < n)
//		{
//			if (nums1[i] > nums2[j])
//			{
//				temp.push_back(nums2[j++]);
//			}
//			else
//			{
//				temp.push_back(nums1[i++]);
//			}
//		}
//		while (i < m)
//		{
//			temp.push_back(nums1[i++]);
//		}
//		while (j < n)
//		{
//			temp.push_back(nums2[j++]);
//		}
//
//		double result = 0.0;
//		int o = temp.size();
//		if (o % 2 == 1)
//		{
//			result = (double)temp[o / 2];
//		}
//		else
//		{
//			result = ((double)(temp[o / 2] + temp[o / 2 - 1])) / 2;
//		}
//		return result;
//	}
//};