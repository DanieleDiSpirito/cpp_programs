#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	unordered_map<string, long long int> mp;
	int q, k;
	cin >> q >> k;
	for(; q > 0; q--) {
		string name;
		int E;
		cin >> name >> E;
		mp[name] += E;
	}
	vector<long long int> exp(mp.size(), 0);
	int i = 0;
	for(const auto& el: mp) {
		exp[i++] = el.second;
	}
	sort(exp.begin(), exp.end(), [](const long long int a, const long long int b) {
		return a > b;
	});
	long long int res = 0;
	i = 0;
	for(; k > 0 && i < exp.size(); k--) {
		res += exp[i++];
	}
	cout << res;
	return 0;
}
