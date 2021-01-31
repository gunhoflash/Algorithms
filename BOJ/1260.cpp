#include <iostream>
#include <queue>
#include <stack>
#include <vector>

using namespace std;

int main(void) {
	int
		N, // the number of vertices
		M, // the number of edges
		V, // starting vertex
		v1, v2; // vertices

	vector<bool>
		is_visited;

	vector<vector<bool>>
		is_adjacent;

	queue<int>
		visiting_queue;

	stack<int>
		visiting_stack;

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N >> M >> V;

	// init vectors
	is_visited.resize(N + 1, false);
	is_adjacent.resize(N + 1, vector<bool>(N + 1, false));

	// set edges
	while (M--) {
		cin >> v1 >> v2;

		is_adjacent[v1][v2] = true;
		is_adjacent[v2][v1] = true;
	}

	// DFS
	visiting_stack.push(V);
	while (!visiting_stack.empty()) {
		// pop one
		v1 = visiting_stack.top();
		visiting_stack.pop();

		if (is_visited[v1]) continue;
		is_visited[v1] = true;
		cout << v1 << ' ';

		// check adjacent
		for (int v2 = N; v2 > 0; v2--) {
			if (is_adjacent[v1][v2] && !is_visited[v2]) {
				visiting_stack.push(v2);
			}
		}
	}

	// init {is_visited}
	is_visited.assign(N + 1, false);

	cout << '\n';

	// BFS
	visiting_queue.push(V);
	is_visited[V] = true;
	while (!visiting_queue.empty()) {
		// pop one
		v1 = visiting_queue.front();
		visiting_queue.pop();

		cout << v1 << ' ';

		// check adjacent
		for (int v2 = 1; v2 <= N; v2++) {
			if (is_adjacent[v1][v2] && !is_visited[v2]) {
				is_visited[v2] = true;
				visiting_queue.push(v2);
			}
		}
	}

	return 0;
}