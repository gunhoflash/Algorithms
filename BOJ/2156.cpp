#include <iostream>
#include <vector>

using namespace std;

int max3(int a, int b, int c) {
	return a > b ? (a > c ? a : c) : (b > c ? b : c);
}

int main(void) {
	int n;
	vector<vector<int>> max_when_drink_sequence;

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	// init vectors with 2 bumps
	cin >> n;
	max_when_drink_sequence.resize(n + 1, vector<int>(3, 0));

	// get all drinks
	for (int i = 1; i <= n; i++) {
		int v;
		cin >> v;

		max_when_drink_sequence[i][0] = max3(
			max_when_drink_sequence[i - 1][0],
			max_when_drink_sequence[i - 1][1],
			max_when_drink_sequence[i - 1][2]
		);
		max_when_drink_sequence[i][1] = max_when_drink_sequence[i - 1][0] + v;
		max_when_drink_sequence[i][2] = max_when_drink_sequence[i - 1][1] + v;
	}

	// print the answer
	cout << max3(max_when_drink_sequence[n][0], max_when_drink_sequence[n][1], max_when_drink_sequence[n][2]);
}
