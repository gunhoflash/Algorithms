#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

int main(void) {
	int i, N;
	string str;
	map<string, int> words;
	vector<pair<int, string>> answer;

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	// get data
	cin >> N;
	for (i = 0; i < N; i++) {
		cin >> str;
		words[str] = 0;
	}

	// map to vector
	for (auto kv : words) {
		answer.push_back({ kv.first.length(), kv.first });
	}

	// sort and print out
	N = answer.size();
	sort(answer.begin(), answer.end());
	for (i = 0; i < N; i++) {
		cout << answer[i].second << '\n';
	}

	return 0;
}