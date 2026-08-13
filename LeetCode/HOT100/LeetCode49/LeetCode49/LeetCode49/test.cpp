class Solution {
public:
	vector<vector<string>> groupAnagrams(vector<string>& strs) {
		// 键值对[key, value]
		// 这里key是字母排序之后的字符串，如果之后的排序后的字符串相等的话，那么就放在同一个vector中
		unordered_map<string, vector<string>> mp;
		for (auto& e : strs)
		{
			// str临时值，保存排序后的字符串，也是插入key值
			string str = e;
			sort(str.begin(), str.end());
			mp[str].emplace_back(e);
		}

		// 这里不用auto的原因是mp的value不是一个类型，而是一个string类型的数组
		vector<vector<string>> ans;
		for (auto it = mp.begin(); it != mp.end(); ++it)
		{
			ans.emplace_back(it->second);
		}
		return ans;
	}
};