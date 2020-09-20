#include <iostream>

using namespace std;

int parent[1000001];

int get_parent(int n) {
	if (parent[n] == n) {
		// n is root
		return n;
	} else {
		// update parent and return
		parent[n] = get_parent(parent[n]);
		return parent[n];
	}
}

void merge(int a, int b) {
	int root_a = get_parent(a);
	int root_b = get_parent(b);

	// already merged
	if (root_a == root_b) return;

	// merge root_b into root_a
	parent[root_b] = root_a;
}

int main(void) {
	int
		i, // indexer
		n, // the number of elements
		m, // the number of operations
		operation, a, b; // operation

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	// get data
	cin >> n >> m;

	// init {parent}
	for (i = 0; i <= n; i++) {
		parent[i] = i;
	}

	while (m--) {
		cin >> operation >> a >> b;

		if (operation == 0) {
			// merge
			merge(a, b);
		} else {
			// check
			cout << (get_parent(a) == get_parent(b) ? "YES" : "NO") << '\n';
		}
	}

	return 0;
}