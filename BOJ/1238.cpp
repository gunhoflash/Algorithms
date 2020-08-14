#include <iostream>
#include <vector>

#define DISTANCE_MAX 1000000

using namespace std;

int main(void) {
	int
		i, j, k, // indexer
		N,       // the number of towns
		M,       // the number of way
		X,       // party place
		A, B, T, // town and walktime
		max_time;
	vector<vector<int>> distance; // index 0 never used

	// get data: N and M
	cin >> N >> M >> X;
	distance.resize(N + 1, vector<int>(N + 1, DISTANCE_MAX));
	while (M--) {
		cin >> A >> B >> T;
		distance[A][B] = T;
	}

	// use Floyd-Warshall Algorithm

	// init distance {i} to {i}
	for (k = 1; k <= N; k++) {
		distance[k][k] = 0;
		for (i = 1; i <= N; i++) {
			for (j = 1; j <= N; j++) {
				if (distance[i][j] > distance[i][k] + distance[k][j])
					distance[i][j] = distance[i][k] + distance[k][j];
			}
		}
	}

	// find the friend with min-bacon number
	max_time = 0;
	for (i = 1; i <= N; i++) {
		T = distance[i][X] + distance[X][i];

		if (T > max_time) {
			max_time = T;
		}
	}
	cout << max_time;

	return 0;
}