#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int main(void) {
	int N;
	vector<vector<int>> adjacents;
	vector<int> parent;

	queue<int> visiting_queue;

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	// get the number of nodes
	cin >> N;

	// init tree (index 0 is dummy)
	adjacents.resize(N + 1);

	// get all edges
	for (int i = 1; i < N; i++) {
		int p, q;
		cin >> p >> q;
		adjacents[p].push_back(q);
		adjacents[q].push_back(p);
	}

	// init parent (index 0 is dummy)
	parent.resize(N + 1, 0);

	// start from the root: node 1
	parent[1] = 1;
	visiting_queue.push(1);
	while (!visiting_queue.empty()) {
		// pop one
		int cur = visiting_queue.front();
		visiting_queue.pop();

		// visit all adjacent nodes
		for (int adj : adjacents[cur]) {
			if (parent[adj] == 0) {
				// if not visited, set parent and push to queue
				parent[adj] = cur;
				visiting_queue.push(adj);
			}
		}
	}

	// print parents
	for (int i = 2; i <= N; i++) {
		cout << parent[i] << '\n';
	}

	return 0;
}