#define min2(a, b) (a < b ? a : b)
#define min3(a, b, c) (a < b ? min2(a, c) : min2(b, c))

#include <iostream>

using namespace std;

int main(void) {
	int
		N,
		R[1001] = { 0 },
		G[1001] = { 0 },
		B[1001] = { 0 };

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N;
	for (int i = 1; i <= N; i++) {
		cin >> R[i] >> G[i] >> B[i];
		R[i] += min2(G[i - 1], B[i - 1]);
		G[i] += min2(R[i - 1], B[i - 1]);
		B[i] += min2(R[i - 1], G[i - 1]);
	}

	cout << min3(R[N], G[N], B[N]);

	return 0;
}
