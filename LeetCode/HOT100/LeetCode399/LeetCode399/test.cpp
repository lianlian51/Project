class Solution {
public:
	vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
		int nars = 0;
		unordered_map<string, int> ques;
		// 计算出所有不重复的个数，个数存储在ques中的值中
		int len = equations.size();
		for (int i = 0; i < len; ++i)
		{
			if (ques.find(equations[i][0]) == ques.end()){
				ques[equations[i][0]] = nars++;
			}
			if (ques.find(equations[i][1]) == ques.end()){
				ques[equations[i][1]] = nars++;
			}
		}

		// 弗洛伊德算法，先将图计算出来，将已知的数字除法放在二维数组中
		vector<vector<double>> gragh(nars, vector<double>(nars, -1.0));
		for (int i = 0; i < len; ++i)
		{
			int va = ques[equations[i][0]];
			int vb = ques[equations[i][1]];
			gragh[va][vb] = values[i];
			gragh[vb][va] = 1.0 / values[i];
		}

		// 计算出字符组合相除的情况
		for (int k = 0; k < nars; ++k)
		{
			for (int i = 0; i < nars; ++i)
			{
				for (int j = 0; j < nars; ++j)
				{
					if (gragh[i][k] > 0 && gragh[k][j] > 0)
					{
						gragh[i][j] = gragh[i][k] * gragh[k][j];
					}
				}
			}
		}

		vector<double> ret;
		for (auto & e : queries)
		{
			double result = -1.0;
			if (ques.find(e[0]) != ques.end() && ques.find(e[1]) != ques.end())
			{
				int ia = ques[e[0]], ib = ques[e[1]];
				result = gragh[ia][ib];
			}
			ret.push_back(result);
		}
		return ret;
	}
};