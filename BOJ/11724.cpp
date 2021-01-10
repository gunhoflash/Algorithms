#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main(void) {
	int
		i, // indexer
		N, // the number of vertices
		M, // the number of edges
		u, v,
		n_connected_component;

	vector<bool>
		is_visited;

	vector<vector<int>>
		adjacents; // index 0 not used

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	// get the number of vertices and edges
	cin >> N >> M;
	is_visited.resize(N + 1, false);
	adjacents.resize(N + 1);

	// get all edges
	for (i = 0; i < M; i++) {
		cin >> u >> v;
		adjacents[u].push_back(v);
		adjacents[v].push_back(u);
	}

	// find all connected components
	n_connected_component = 0;
	for (i = 1; i <= N; i++) {
		if (is_visited[i]) continue;

		is_visited[i] = true;
		n_connected_component++;

		// visit all using BFS
		queue<int> visiting_queue;
		visiting_queue.push(i);
		while (!visiting_queue.empty()) {
			// pop one
			int now = visiting_queue.front();
			visiting_queue.pop();

			// visit adjacents
			for (auto adjacent : adjacents[now]) {
				if (!is_visited[adjacent]) {
					is_visited[adjacent] = true;
					visiting_queue.push(adjacent);
				}
			}
		}
	}

	// print the answer
	cout << n_connected_component;

	return 0;
}