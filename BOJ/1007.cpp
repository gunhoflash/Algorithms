#include <algorithm>
#include <float.h>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

struct Point {
	int x;
	int y;
};

int main(void) {
	int
		i, j, // indexers
		T, // the number of test cases
		N, // the number of points
		bit,
		n_1s, // the number of 1 at the bit mask
		bit_mask_max;

	long double
		square_length,
		min_square_length;

	Point
		sum,
		points[20];

	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout << fixed;
	cout.precision(9);

	// get the number of test cases
	cin >> T;
	while (T--) {
		// get all points
		cin >> N;
		for (i = 0; i < N; i++) {
			cin >> points[i].x >> points[i].y;
		}

		// init
		min_square_length = LDBL_MAX;

		// check all combinations using bit mask
		bit_mask_max = 1 << N;
		for (i = 0; i < bit_mask_max; i++) {
			// init sum
			sum.x = sum.y = 0;

			// check half 0 and half 1
			n_1s = 0;
			for (j = 0; j < N; j++) {
				bit = (i >> j) & 1;
				sum.x += (bit * 2 - 1) * points[j].x;
				sum.y += (bit * 2 - 1) * points[j].y;
				n_1s += bit;
			}

			// invalid combination
			if (n_1s != N / 2) continue;

			// calculate square of length of sum
			square_length = (long double) sum.x * sum.x + (long double) sum.y * sum.y;
			min_square_length = min(min_square_length, square_length);
		}

		// print the answer
		cout << sqrtl(min_square_length) << '\n';
	}

	return 0;
}