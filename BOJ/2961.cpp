#include <iostream>
#include <cmath>

using namespace std;

int main() {
	int s[10] = { 0 };
	int b[10] = { 0 };

	int N;
	cin >> N;

	// init s and b
	for (int i = 0; i < N; i++) {
		cin >> s[i] >> b[i];
	}

	// find min gap from all possible combinations
	int min_gap = 0x7fffffff;
	for (int bits = (1 << N) - 1; bits > 0; bits--) {
		int mul_s = 1;
		int sum_b = 0;

		for (int i = 0; i < N; i++) {
			if (bits & (1 << i)) {
				mul_s *= s[i];
				sum_b += b[i];
			}
		}

		min_gap = min(min_gap, abs(mul_s - sum_b));
	}

	// print result
	cout << min_gap;
}