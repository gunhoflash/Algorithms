#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main(void) {
	int
		r, c, // indexer, rw and column
		N, // the size of row and column
		n_T, // the number of T
		min_n_T, // the minimum number of T
		row_bitmask,
		row_bitmask_max;

	bool
		coin_T_original[20][20],
		coin_T[20][20];

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	// set all coins
	cin >> N;
	for (r = 0; r < N; r++) {
		for (c = 0; c < N; c++) {
			char ch;
			cin >> ch;
			coin_T_original[r][c] = (ch == 'T');
		}
	}

	row_bitmask_max = 1 << N;

	min_n_T = N * N;
	for (row_bitmask = 1; row_bitmask < row_bitmask_max; row_bitmask++) {
		// copy
		for (r = 0; r < N; r++) {
			for (c = 0; c < N; c++) {
				coin_T[r][c] = coin_T_original[r][c];
			}
		}

		// filp rows
		for (r = 0; r < N; r++) {
			if ((row_bitmask >> r) & 1) {
				// flip row
				for (c = 0; c < N; c++) {
					coin_T[r][c] = !coin_T[r][c];
				}
			}
		}

		// count all T
		n_T = 0;
		for (c = 0; c < N; c++) {
			// count all T in a column
			int column_n_T = 0;
			for (r = 0; r < N; r++) {
				column_n_T += (coin_T[r][c] ? 1 : 0);
			}

			// accumulate the minimum number of T when flip the column or not
			n_T += min(column_n_T, N - column_n_T);
		}

		// update {min_n_T}
		min_n_T = min(min_n_T, n_T);
	}

	// print the answer: the minimum number of T
	cout << min_n_T;

	return 0;
}