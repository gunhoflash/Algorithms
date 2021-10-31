#include <iostream>

using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int T, N, M, _;
	cin >> T;
	while (T--) {
		cin >> N >> M;
		while (M--) cin >> _ >> _;
		cout << N - 1 << '\n';
	}

	return 0;
}