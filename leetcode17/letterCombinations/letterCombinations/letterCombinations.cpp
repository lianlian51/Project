class Solution {
public:
	map<char, string> Map{
		{ '2', "abc" }, { '3', "def" }, { '4', "ghi" }, { '5', "jkl" }, { '6', "mno" }, { '7', "pqrs" }, { '8', "tuv" }, { '9', "wxyz" }
	};
	// 保存返回结果
	vector<string> result;
	// 临时的
	string temp;

	// index对应每个数字按键的字符的个数
	void DFS(int index, string& digits)
	{
		// index记录此时tmp中字符的个数，如果和digits的相等，就将temp写到result中
		if (digits.size() == index)
		{
			result.push_back(temp);
			return;
		}

		// digits[index]表示字符，Map[digits[index]][i]表示数字字符对应的英文字母
		for (int i = 0; i < Map[digits[index]].size(); ++i)
		{
			temp.push_back(Map[digits[index]][i]);
			DFS(index + 1, digits);
			temp.pop_back();
		}
	}

	vector<string> letterCombinations(string digits) {
		if (digits.size() == 0)
			return result;
		DFS(0, digits);
		return result;
	}
};
