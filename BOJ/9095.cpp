#include <iostream>

using namespace std;

int main(void) {
	int T, n, ways123[11];

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	ways123[1] = 1; // 1
	ways123[2] = 2; // 1 + 1, 2
	ways123[3] = 4; // 1 + 1 + 1, 1 + 2, 2 + 1, 3

	// complete ways123
	for (n = 4; n < 11; n++) {
		ways123[n] = ways123[n - 1] + ways123[n - 2] + ways123[n - 3];
	}

	// answer the questions
	cin >> T;
	while (T--) {
		cin >> n;
		cout << ways123[n] << '\n';
	}

	return 0;
}