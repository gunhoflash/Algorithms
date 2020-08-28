#include <iostream>
#include <vector>
#include <climits>

using namespace std;

int main(void) {
	int
		i, k, // indexer
		N, // the number of cities
		M, // the number of routes
		A, B, C; // info of a route

	// index 0 as city never used

	vector<vector<int>> edges; // [[ soruce, destination, cost ], ... ]
	vector<long long> distances;

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	// set the number of cities and init all distances as MAX
	cin >> N;
	distances.resize(N + 1, LLONG_MAX);
	distances[1] = 0;

	// set the number of routes
	cin >> M;
	for (i = 0; i < M; i++) {
		// move from ${A} to ${B} with time C
		cin >> A >> B >> C;
		edges.push_back({ A, B, C });
	}

	// use Bellman-Ford Algorithm

	for (k = 0; k < M; k++) {
		for (i = 0; i < M; i++) {
			A = edges[i][0];
			B = edges[i][1];
			C = edges[i][2];

			// update shortest distance
			if (distances[A] == LLONG_MAX) continue;
			else if (distances[B] > distances[A] + C) {
				distances[B] = distances[A] + C;
			}
		}
	}

	// check for all edges to find a negative-cycle
	for (i = 0; i < M; i++) {
		A = edges[i][0];
		B = edges[i][1];
		C = edges[i][2];

		if (distances[A] == LLONG_MAX) continue;
		else if (distances[B] > distances[A] + C) {
			cout << "-1";
			return 0;
		}
	}

	// print all distances
	for (i = 2; i <= N; i++) {
		if (distances[i] == LLONG_MAX) {
			cout << "-1\n";
		} else {
			cout << distances[i] << '\n';
		}
	}

	return 0;
}