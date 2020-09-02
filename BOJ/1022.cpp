#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

inline int get_digits(int n) {
	int digits = 0;
	while (n) {
		n /= 10;
		digits++;
	}
	return digits;
}

inline int find_number(int row, int column) {
	int
		layer_start,
		layer_end,
		layer_n_numbers_div4,
		layer,
		answer;

	layer = max(abs(row), abs(column));
	if (layer == 0) {
		return 1;
	}

	layer_start = pow((layer * 2) - 1, 2) + 1;
	layer_end   = pow((layer * 2) + 1, 2);
	layer_n_numbers_div4 = (layer_end - layer_start + 1) / 4;

	// bottom line
	if (row == layer) {
		return layer_end - (layer - column);
	}
	
	// left line
	if (column == -layer) {
		return layer_end - layer_n_numbers_div4 - (layer - row);
	}

	// top line
	if (row == -layer) {
		return layer_end - 2 * layer_n_numbers_div4 - (layer + column);
	}

	// right line
	return layer_end - 3 * layer_n_numbers_div4 - (layer + row);
}

int main(void) {
	int
		r, c, // indexer
		n, // a found number
		max_abs, // maximum abs number
		digits, max_digits, // digits of a number
		r1, c1, r2, c2;

	int answers[50][5];

	// get data
	cin >> r1 >> c1 >> r2 >> c2;

	// find all numbers
	max_abs = 1;
	for (r = r1; r <= r2; r++) {
		for (c = c1; c <= c2; c++) {
			n = find_number(r, c);
			max_abs = max(max_abs, abs(n));
			answers[r - r1][c - c1] = n;
		}
	}

	// calculate digits of the {max_abs}
	max_digits = 0;
	while (max_abs) {
		max_abs /= 10;
		max_digits++;
	}

	// print the answer
	for (r = r1; r <= r2; r++) {
		for (c = c1; c <= c2; c++) {
			n = answers[r - r1][c - c1];
			digits = get_digits(n);

			// print white spaces
			while (digits++ < max_digits) cout << ' ';

			// print a number
			cout << n << ' ';
		}
		cout << '\n';
	}

	return 0;
}