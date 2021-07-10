#include <algorithm>
#include <iostream>

using namespace std;

int main(void) {
	int T;

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> T;
	while (T--) {
		int N, M, n_iterate;
		long long answer = 1;

		cin >> N >> M;

		// calculate and print out M_C_N
		n_iterate = min(M - N, N);
		for (int i = 0; i < n_iterate; i++) answer *= (M - i);
		for (int i = 0; i < n_iterate; i++) answer /= (i + 1);
		cout << answer << '\n';
	}
	return 0;
}