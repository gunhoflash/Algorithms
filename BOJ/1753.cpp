#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <vector>
#include <climits>

using namespace std;

int main(void) {
	int
		i, // indexer
		now, // now visiting vertex
		V, // the number of vertices
		E, // the number of edges
		K, // starting vertex
		u, v; // info of an edge: from {u} to {v} with cost {w}

	int
		cost, // now visiting vertex's total cost
		w; // info of an edge: from {u} to {v} with cost {w}

	vector<map<int, int>> adjacents; // [[ ( destination: cost ), ... ], ... ]
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>> > visiting_queue; // [ [ total cost, destination ], ... ]
	vector<int> distances;

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	// set the number of vertex and edge
	cin >> V >> E;
	adjacents.resize(V + 1, map<int, int>());
	distances.resize(V + 1, INT_MAX);

	// set starting vertex
	cin >> K;

	// set all edges
	while (E--) {
		cin >> u >> v >> w;
		if (adjacents[u].find(v) == adjacents[u].end()) {
			adjacents[u][v] = w;
		} else if (adjacents[u][v] > w) {
			adjacents[u][v] = w;
		}
	}

	// BFS starting from K
	distances[K] = 0;
	visiting_queue.push({ 0, K });
	while (!visiting_queue.empty()) {
		// pop one
		cost = visiting_queue.top().first;
		now  = visiting_queue.top().second;
		visiting_queue.pop();

		// shorter route already found
		if (cost > distances[now]) continue;

		// look for all adjacent vertices
		for (auto kv : adjacents[now]) {
			v = kv.first;
			w = kv.second + cost;
			if (distances[v] > w) {
				distances[v] = w;
				visiting_queue.push({ w, v });
			}
		}
	}

	// print all distances
	for (i = 1; i <= V; i++) {
		if (distances[i] == INT_MAX) {
			cout << "INF\n";
		} else {
			cout << distances[i] << '\n';
		}
	}

	return 0;
}