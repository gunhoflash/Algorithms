#include <iostream>

using namespace std;

int w_dp[21][21][21];

// calculate w(a, b, c)
inline int w(int a, int b, int c) {
	if (a <= 0 || b <= 0 || c <= 0) {
		if (
			a >= 0 && a <= 20 && 
			b >= 0 && b <= 20 &&
			c >= 0 && c <= 20
		) {
			w_dp[a][b][c] = 1;
		}

		return 1;
	}

	if (a > 20 || b > 20 || c > 20) {
		return w_dp[20][20][20];
	}

	if (a < b && b < c) {
		w_dp[a][b][c] = w_dp[a][b][c - 1] + w_dp[a][b - 1][c - 1] - w_dp[a][b - 1][c];
		return w_dp[a][b][c];
	}

	w_dp[a][b][c] = w_dp[a - 1][b][c] + w_dp[a - 1][b - 1][c] + w_dp[a - 1][b][c - 1] - w_dp[a - 1][b - 1][c - 1];
	return w_dp[a][b][c];
}

int main(void) {
	int a, b, c;

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	// init {w_dp}
	for (a = 0; a <= 20; a++) {
		for (b = 0; b <= 20; b++) {
			for (c = 0; c <= 20; c++) {
				w(a, b, c);
			}
		}
	}

	// test all
	while (true) {
		// get data
		cin >> a >> b >> c;

		// handle exception: the end
		if (a == -1 && b == -1 && c == -1) break;

		// print the answer
		cout << "w(" << a << ", " << b << ", " << c << ") = " << w(a, b, c) << '\n';
	}

	return 0;
}