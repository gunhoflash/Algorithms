#include <iostream>
#include <map>

using namespace std;

int main(void) {
	int N, M, number_of_dbj;
	string str;
	map<string, int> names;

	// get data
	cin >> N >> M;

	// get d
	while (N--) {
		cin >> str;
		names[str] = 1;
	}

	// get b, count dbj
	number_of_dbj = 0;
	while (M--) {
		cin >> str;
		if (names[str]) {
			names[str]++;
			number_of_dbj++;
		}
	}

	// print out all dbj
	cout << number_of_dbj << '\n';
	for (auto kv : names) {
		if (kv.second == 2) {
			cout << kv.first << '\n';
		}
	}

	return 0;
}