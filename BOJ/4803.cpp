#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Node {
	bool is_visited;
	vector<int> adjacents;
};

int get_number_of_tree(int n, int m) {
	int n_tree = 0;
	vector<Node> nodes(n + 1);

	// config adjacents
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		nodes[a].adjacents.push_back(b);
		nodes[b].adjacents.push_back(a);
	}

	// check all nodes
	for (int i = n; i; i--) {
		if (nodes[i].is_visited) continue;

		bool is_tree = true;

		// bfs from i
		queue<int> q;
		q.push(i);
		while (!q.empty()) {
			// pop one
			int cur = q.front();
			q.pop();

			if (nodes[cur].is_visited) {
				// graph has a cycle
				is_tree = false;
				continue;
			}
			nodes[cur].is_visited = true;

			// visit adjacents
			for (int adj : nodes[cur].adjacents) {
				if (nodes[adj].is_visited) continue;
				q.push(adj);
			}
		}

		// a new tree found
		if (is_tree) n_tree++;
	}

	return n_tree;
}

int main() {
	int test_number = 0;

	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	while (true) {
		int n, m;
		cin >> n >> m;
		if (n == 0 && m == 0) break;

		test_number++;
		cout << "Case " << test_number << ": ";

		int n_tree = get_number_of_tree(n, m);
		switch (n_tree) {
			case 0:
				cout << "No trees.\n";
				break;
			case 1:
				cout << "There is one tree.\n";
				break;
			default:
				cout << "A forest of " << n_tree << " trees.\n";
				break;
		}
	}
	return 0;
}
