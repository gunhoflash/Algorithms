#include <iostream>
#include <climits>

using namespace std;

int main(void) {
	int
		i, j, k, // indexer
		n, // the number of cities
		m, // the number of buses
		a, b, c; // info of an edge: from {a} to {b} with cost {c}

	int distances[101][101];

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	// set the number of cities and buses
	cin >> n >> m;

	// init distances
	for (i = 1; i <= n; i++) {
		for (j = 1; j <= n; j++) {
			distances[i][j] = INT_MAX;
		}
	}

	// set all buses
	while (m--) {
		cin >> a >> b >> c;
		if (distances[a][b] > c) {
			distances[a][b] = c;
		}
	}

	// use Floyd-Warshall Algorithm
	for (k = 1; k <= n; k++) {
		distances[k][k] = 0;
		for (i = 1; i <= n; i++) {
			for (j = 1; j <= n; j++) {
				a = distances[i][j];
				b = distances[i][k];
				c = distances[k][j];
				if (b < INT_MAX && c < INT_MAX) {
					if (a > b + c) {
						distances[i][j] = b + c;
					}
				}
			}
		}
	}

	// print all distances
	for (i = 1; i <= n; i++) {
		for (j = 1; j <= n; j++) {
			if (distances[i][j] == INT_MAX) {
				cout << "0 ";
			} else {
				cout << distances[i][j] << ' ';
			}
		}
		cout << '\n';
	}

	return 0;
}