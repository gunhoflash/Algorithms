#include <iostream>

using namespace std;

int main(void) {
	int map[100][100] = { 0 };
	int
		i, j, // indexers
		N, // the size of the map
		L, // the length of slope
		before_height,
		now_height,
		n_row,
		n_remained_for_slope,
		answer;

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	// get data
	cin >> N >> L;
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			cin >> map[i][j];
		}
	}

	// answer = N * 2
	answer = N << 1;

	// check rows
	for (i = 0; i < N; i++) {
		n_row = 1;
		n_remained_for_slope = 0;
		before_height = map[i][0];
		for (j = 1; j < N; j++) {
			now_height = map[i][j];

			// check height
			if (now_height == before_height) {
				// same height
				if (n_remained_for_slope > 0) {
					n_remained_for_slope--;
				} else {
					n_row++;
				}
			} else {
				// not same height

				if (n_remained_for_slope > 0) {
					// can't place the slope
					break;
				}

				if (now_height == before_height - 1) {
					// lower height
					n_remained_for_slope = L - 1;
					n_row = 0;
				} else if (now_height == before_height + 1) {
					// higher height
					if (n_row < L) {
						// can't place the slope
						break;
					}
					n_row = 1;
				} else {
					// big gap
					break;
				}

				before_height = now_height;
			}
		}

		if (j < N || n_remained_for_slope > 0) {
			// can't place the slope
			answer--;
		}
	}

	// check columns
	for (j = 0; j < N; j++) {
		n_row = 1;
		n_remained_for_slope = 0;
		before_height = map[0][j];
		for (i = 1; i < N; i++) {
			now_height = map[i][j];

			// check height
			if (now_height == before_height) {
				// same height
				if (n_remained_for_slope > 0) {
					n_remained_for_slope--;
				} else {
					n_row++;
				}
			} else {
				// not same height

				if (n_remained_for_slope > 0) {
					// can't place the slope
					break;
				}

				if (now_height == before_height - 1) {
					// lower height
					n_remained_for_slope = L - 1;
					n_row = 0;
				} else if (now_height == before_height + 1) {
					// higher height
					if (n_row < L) {
						// can't place the slope
						break;
					}
					n_row = 1;
				} else {
					// big gap
					break;
				}

				before_height = now_height;
			}
		}

		if (i < N || n_remained_for_slope > 0) {
			// can't place the slope
			answer--;
		}
	}

	// print the answer
	cout << answer;

	return 0;
}