#include <iostream>

using namespace std;

int row_sum[1025][1025] = { 0 };

inline void test_sum() {
	int
		x1, y1, x2, y2,
		sum = 0;

	cin >> x1 >> y1 >> x2 >> y2;

	while (x1 <= x2) {
		sum += row_sum[x1][y2] - row_sum[x1][y1 - 1];
		x1++;
	}

	cout << sum << '\n';
}

int main(void) {
	int
		N, // the size of table
		M; // the number of tests

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N >> M;

	// get numbers
	for (int x = 1; x <= N; x++) {
		for (int y = 1; y <= N; y++) {
			cin >> row_sum[x][y];
		}
	}

	// calculate every row sum
	for (int x = 1; x <= N; x++) {
		for (int y = 2; y <= N; y++) {
			row_sum[x][y] += row_sum[x][y - 1];
		}
	}

	// do tests
	while (M--) {
		test_sum();
	}

	return 0;
}