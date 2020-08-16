#include <iostream>
#include <map>
#include <string>

using namespace std;

int main(void) {
	int N, M, answer;
	string str;
	map<string, bool> set;

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	// get N and M
	// make the set
	cin >> N >> M;
	while (N--) {
		cin >> str;
		set.insert({str, false});
	}

	// count the answer
	while (M--) {
		cin >> str;
		if (set.find(str) != set.end()) {
			answer++;
		}
	}
	cout << answer;

	return 0;
}