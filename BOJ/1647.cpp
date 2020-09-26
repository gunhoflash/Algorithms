#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int get_parent(int n, vector<int> &parent) {
	if (parent[n] == n) {
		return n;
	} else {
		return parent[n] = get_parent(parent[n], parent);
	}
}

bool merge(int a, int b, vector<int> &parent) {
	int root_a = get_parent(a, parent);
	int root_b = get_parent(b, parent);

	if (root_a == root_b) {
		// already merged
		return false;
	}

	// merge
	parent[root_b] = root_a;
	return true;
}

int main(void) {
	int
		i, // indexer
		sum_weight,
		max_weight,
		V, // the number of vertex
		E, // the number of edge
		A, B, C; // info of an edge: A and B are connected with weight C

	vector<int> parent;
	vector<vector<int>> edges; // [ weight, vertex1, vertex2 ]

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	// get data
	cin >> V >> E;

	// init vectors
	parent.resize(V + 1);
	edges.resize(E, vector<int>(3));

	// set parent for all vertexes
	for (i = 1; i <= V; i++) {
		parent[i] = i;
	}

	// add all edges
	for (i = 0; i < E; i++) {
		cin >> A >> B >> C;
		edges[i][0] = C;
		edges[i][1] = A;
		edges[i][2] = B;
	}

	// sort by weight
	sort(edges.begin(), edges.end());

	// look for minimum weight edges
	sum_weight = 0;
	max_weight = 0;
	for (i = 0; i < E; i++) {
		C = edges[i][0];
		A = edges[i][1];
		B = edges[i][2];

		if (merge(A, B, parent)) {
			sum_weight += C;
			max_weight = C > max_weight ? C : max_weight;
		}
	}

	// print the answer
	cout << sum_weight - max_weight;

	return 0;
}