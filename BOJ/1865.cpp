#include <iostream>
#include <climits>

using namespace std;

int main(void) {
	int
		i, j, k, // indexers
		size, // size of a vector
		TC, // the number of test case
		N, // the number of points
		M, // the number of roads
		W, // the number of wormholes
		S, E, T, // info of a road or wormhole
		ij, ik, kj; // distances

	int distances[501][501];

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> TC;
	while (TC--) {
		cin >> N >> M >> W;

		// init {distances}
		for (i = 1; i <= N; i++) {
			for (j = 1; j <= N; j++) {
				distances[i][j] = INT_MAX;
			}
			distances[i][i] = 0;
		}

		// set roads
		while (M--) {
			cin >> S >> E >> T;

			if (distances[S][E] > T) {
				distances[S][E] = T;
			}
			if (distances[E][S] > T) {
				distances[E][S] = T;
			}
		}

		// set wormholes
		while (W--) {
			cin >> S >> E >> T;

			T *= -1;
			if (distances[S][E] > T) {
				distances[S][E] = T;
			}
		}

		// use Floyd-Warshall Algorithm
		for (k = 1; k <= N; k++) {
			for (i = 1; i <= N; i++) {
				for (j = 1; j <= N; j++) {
					ij = distances[i][j];
					ik = distances[i][k];
					kj = distances[k][j];

					if (ik == INT_MAX || kj == INT_MAX) continue;
					if (ij > ik + kj) {
						distances[i][j] = ik + kj;
					}
				}
			}
		}

		for (i = 1; i <= N; i++) {
			if (distances[i][i] < 0) {
				cout << "YES\n";
				break;
			}
		}
		if (i > N) {
			cout << "NO\n";
		}
	}

	return 0;
}