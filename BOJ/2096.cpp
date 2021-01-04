#include <iostream>

#define min2(a, b) (a < b ? a : b)
#define min3(a, b, c) (a < b ? min2(a, c) : min2(b, c))

#define max2(a, b) (a > b ? a : b)
#define max3(a, b, c) (a > b ? max2(a, c) : max2(b, c))

using namespace std;

int main(void) {
	int
		i, //indexer
		N, // the number of lines
		a, b, c, // numbers in a line
		m0, m1, m2, // for temp
		min[3] = { 0 },
		max[3] = { 0 };

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	// get the number of lines
	cin >> N;

	// get all numbers
	for (i = 0; i < N; i++) {
		cin >> a >> b >> c;

		// min
		m0 = min[0];
		m1 = min[1];
		m2 = min[2];
		min[0] = min2(m0, m1) + a;
		min[1] = min3(m0, m1, m2) + b;
		min[2] = min2(m1, m2) + c;

		// max
		m0 = max[0];
		m1 = max[1];
		m2 = max[2];
		max[0] = max2(m0, m1) + a;
		max[1] = max3(m0, m1, m2) + b;
		max[2] = max2(m1, m2) + c;
	}

	// print the answer
	cout << max3(max[0], max[1], max[2]) << ' ' << min3(min[0], min[1], min[2]);

	return 0;
}