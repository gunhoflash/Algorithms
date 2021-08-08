#include <iostream>
#include <map>

using namespace std;

#define update_max(target, value) (target = target < value ? value : target)

int main(void) {
	int
		N, // the number of rows
		M, // the number of columns
		K, // allowd maximum number of reverse operation
		answer = 0;
	map<int, map<long long, int>> rows; // key is n_0 and value is map that key is bits and value is count

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	// get all rows
	cin >> N >> M;
	while (N--) {
		// get a row
		string s;
		cin >> s;

		// convert row to long long
		int n_0 = M;
		long long row = 0;
		for (int i = 0; i < M; i++) {
			if (s[i] == '1') {
				n_0--;
				row |= (1LL << i);
			}
		}

		// add to map
		rows[n_0][row]++;
	}

	// check rows only that n_0 is (K - 2*I). (I is some non-negative integer)
	cin >> K;
	for (auto &p : rows) {
		if (p.first <= K && (K - p.first) % 2 == 0) {
			for (auto &q : p.second) {
				update_max(answer, q.second);
			}
		}
	}

	// print answer
	cout << answer;

	return 0;
}
