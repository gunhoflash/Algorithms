#include <climits>
#include <vector>

using namespace std;

int solution(int n, int s, int a, int b, vector<vector<int>> fares) {
	int
		i, j, k, // indexer
		m, // the number of fares
		c, d, f, // info of an fare: from {c} to {d} with cost {f}
		answer;

	int distances[201][201];

	// init distances
	for (i = 1; i <= n; i++) {
		for (j = 1; j <= n; j++) {
			distances[i][j] = INT_MAX;
		}
	}
	m = fares.size();
	for (i = 0; i < m; i++) {
		c = fares[i][0];
		d = fares[i][1];
		f = fares[i][2];
		distances[c][d] = f;
		distances[d][c] = f;
	}

	// use Floyd-Warshall Algorithm
	for (k = 1; k <= n; k++) {
		distances[k][k] = 0;
		for (i = 1; i <= n; i++) {
			for (j = 1; j <= n; j++) {
				f = distances[i][j];
				c = distances[i][k];
				d = distances[k][j];
				if (c < INT_MAX && d < INT_MAX) {
					if (f > c + d) {
						distances[i][j] = c + d;
					}
				}
			}
		}
	}

	answer = INT_MAX;
	for (i = 1; i <= n; i++) {
		f = distances[s][i] + distances[i][a] + distances[i][b];
		if (f < answer)
			answer = f;
	}

	return answer;
}