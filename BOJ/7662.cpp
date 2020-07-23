#include <algorithm>
#include <iostream>
#include <map>

using namespace std;

int main(void) {
	int T, k, n;
	char C;
	map<int, int> dq; // 1 2 3 4 5
	map<int, int>::iterator dq_it;
	map<int, int>::reverse_iterator dq_rit;

	cin.tie(NULL);
	cout.tie(NULL);

	// get the number of test data
	cin >> T;

	// test
	while (T--) {

		// get the number of commands
		cin >> k;
		while (k--) {
			cin >> C >> n;

			if (C == 'I') {
				// insert
				if (dq[n]) {
					dq[n]++;
				} else {
					dq[n] = 1;
				}
			} else {
				// delete
				if (!dq.empty()) {
					// do only when non-empty
					if (n == 1) {
						// pop max
						dq_rit = dq.rbegin();
						if (dq_rit->second == 1) {
							dq.erase(dq_rit->first);
						} else {
							dq_rit->second--;
						}
					} else {
						// pop min
						dq_it = dq.begin();
						if (dq_it->second == 1) {
							dq.erase(dq_it->first);
						} else {
							dq_it->second--;
						}
					}
				}
			}
		}

		// print exist max and min
		if (dq.empty()) {
			cout << "EMPTY\n";
		} else {
			cout << dq.rbegin()->first << ' ' << dq.begin()->first << '\n';
		}
		dq.clear();
	}
	return 0;
}