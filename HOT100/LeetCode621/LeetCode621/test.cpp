class Solution {
public:
	int leastInterval(vector<char>& tasks, int n) {
		int num = tasks.size();
		if (num <= 0)
			return n;
		unordered_map<char, int> mp;
		for (auto& t : tasks)
		{
			mp[t]++;
		}
		int maxM = max_element(mp.begin(), mp.end(), [](const auto& u, const auto & v){
			return u.second < v.second;
		})->second;

		int maxCount = accumulate(mp.begin(), mp.end(), 0, [=](int acc, const auto& v){
			return acc + (maxM == v.second);
		});

		return max((maxM - 1)*(n + 1) + maxCount, static_cast<int>(tasks.size()));
	}
};