class Solution {
public:
	vector<int> findAnagrams(string s, string p) {
		vector<int> ans;
		if (s.size() == 0 || p.size() > s.size()) return ans;

		vector<int> need(128, 0);
		vector<int> windows(128, 0);
		for (auto & e : p)
			need[e]++;
		for (int i = 0; i < p.size() - 1; ++i)
		{
			windows[s[i]]++;
		}
		int l = 0;
		int r = p.size() - 1;
		while (r < s.size())
		{
			windows[s[r++]]++;
			if (windows == need) ans.push_back(l);
			windows[s[l++]]--;
		}
		return ans;
	}
};