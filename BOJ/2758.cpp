#define MAX_N 10
#define MAX_M 2000

#include <iostream>

using namespace std;

int main() {
	long long lotto[MAX_M + 1][MAX_N + 1] = { 0 };

	// init lotto[m][1] as i
	for (int m = 1; m <= MAX_M; m++) {
		lotto[m][1] = m;
	}

	// configure lotto[][2] to lotto[][N]
	for (int n = 2; n <= MAX_N; n++) {
		for (int m = 1; m <= MAX_M; m++) {
			// the number of cases that select m as the last number or not
			lotto[m][n] = lotto[m - 1][n] + lotto[m / 2][n - 1];
		}
	}

	// do all tests
	int T;
	cin >> T;
	while (T--) {
		int n, m;
		cin >> n >> m;
		cout << lotto[m][n] << '\n';
	}
	return 0;
}
