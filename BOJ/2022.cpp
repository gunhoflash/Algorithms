#include <algorithm>
#include <cmath>
#include <iostream>

using namespace std;

int main() {
	double x, y, c, d_min, d_max;
	cin >> x >> y >> c;

	d_min = 0;
	d_max = min(x, y);

	// bi-search the 'd'
	while (d_max - d_min >= 1e-3) {
		double
			d = (d_max + d_min) / 2,
			xh = sqrt(x * x - d * d),
			yh = sqrt(y * y - d * d);

		if ((xh * yh) / (xh + yh) < c) {
			// d is too big
			d_max = d;
		} else {
			// d is too small
			d_min = d;
		}
	}

	// print the answer
	cout << (d_max + d_min) / 2;

	return 0;
}