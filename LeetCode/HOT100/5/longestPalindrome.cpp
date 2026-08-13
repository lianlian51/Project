// 5.最长回文子串
class Solution {
  public:
    // 从中心开始，向两边找最大的回文长度
    int center(string s, int left, int right)
    {
      int l = left;
      int r = right;
      while(l >= 0 && r < s.size() && s[l] == s[r])
      {
        --l, ++r;
      }
      return r - l - 1;
    }

    string longestPalindrome(string s) {
      if(s.size() < 1)
        return "";

      int start = 0;
      int end = 0;
      for(int i = 0; i < s.size(); ++i)
      {
        int len1 = center(s, i, i); // 一个为中心的
        int len2 = center(s, i, i+1); // 两个字符为中心的
        int len = max(len1, len2);  // 比较长度，然后更新长度
        if(len > end  - start)
        {
          start = i - (len-1)/2;
          end = i + len/2;
        }
      }
      string res = s.substr(start, end - start + 1);
      return res;
    }
};
