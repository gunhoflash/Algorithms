#include <iostream>
#include <vector>

#define DISTANCE_MAX 100

using namespace std;

int main(void) {
	int
		i, j, k, // indexer
		N,       // the number of users
		M,       // the number of relationship
		A, B,    // friends with relation
		min_distance,
		min_distancer;
	vector<vector<int>> distance; // index 0 never used

	// get data: N and M
	cin >> N >> M;
	distance.resize(N + 1, vector<int>(N + 1, DISTANCE_MAX));
	while (M--) {
		cin >> A >> B;
		distance[A][B] = distance[B][A] = 1;
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
	min_distance = DISTANCE_MAX;
	for (i = 1; i <= N; i++) {
		k = 0;
		for (j = 1; j <= N; j++) {
			k += distance[i][j];
		}

		if (k >= min_distance) continue;

		min_distance = k;
		min_distancer = i;
	}
	cout << min_distancer;

	return 0;
}