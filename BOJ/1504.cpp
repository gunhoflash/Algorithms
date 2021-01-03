#include <iostream>
#include <vector>

#define MAX_COST 100000000
#define min(a, b) (a < b ? a : b)

using namespace std;

int main(void) {
	int
		i, j, k, // indexers
		N, // the number of vertices
		E, // the number of edges
		a, b, c, // edge's info: between {a} and {b} with cost {c}
		v1, v2, // vertices where we should visit
		path_length;
	
	vector<vector<int>>
		distance; // index 0 not used

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	// get the number of vertices and edges
	cin >> N >> E;

	// init all edges
	distance.resize(N + 1, vector<int>(N + 1, MAX_COST));
	for (i = 0; i < E; i++) {
		cin >> a >> b >> c;
		distance[a][b] = min(distance[a][b], c);
		distance[b][a] = min(distance[b][a], c);
	}

	// do Floyd-Warshall Algorithm
	for (k = 1; k <= N; k++) {
		distance[k][k] = 0;
		for (i = 1; i <= N; i++) {
			for (j = 1; j <= N; j++) {
				if (distance[i][k] + distance[k][j] < distance[i][j]) {
					distance[i][j] = distance[i][k] + distance[k][j];
				}
			}
		}
	}

	// set the vertices where we should visit
	cin >> v1 >> v2;

	// print the shortest route or -1 when no route
	// route 1: start - v1 - v2 - End
	// route 2: start - v2 - v1 - End
	path_length = min(
		distance[1][v1] + distance[v1][v2] + distance[v2][N],
		distance[1][v2] + distance[v2][v1] + distance[v1][N]
	);

	cout << (path_length >= MAX_COST ? -1 : path_length);

	return 0;
}
