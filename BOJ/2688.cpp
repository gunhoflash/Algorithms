#include <iostream>

using namespace std;

// 1 10
// 2 10 + 9 + 8 + 7 + ... + 2 + 1 = 55
// 3 55 + 45 + 36 + ... + 3 + 1 = 130
// ...

void test() {
	int n;
	long long
		sum = 0,
		v[65][10] = { 0 };

	cin >> n;

	// init v
	for (int i = 0; i < 10; i++) {
		sum += v[1][i] = 1;
	}

	for (int i = 2; i <= n; i++) {
		v[i][0] = sum;
		for (int j = 1; j < 10; j++) {
			sum += v[i][j] = v[i][j - 1] - v[i - 1][j - 1];
		}
	}

	cout << sum << '\n';
}

int main(void) {
	int T;
	cin >> T;
	while (T--) test();
}