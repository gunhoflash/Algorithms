#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct edge {
	int u, v, cost;
};

// find group of edge
int find(int x, vector<int> &group) {
	if (group[x] == x) return x;
	return group[x] = find(group[x], group);
}

int main() {
	int n, m;
	vector<int> group;

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> m;

	// init group
	group.resize(n + 1);
	for (int i = 1; i <= n; i++) {
		group[i] = i;
	}

	// get input of all egdes
	vector<edge> edges;
	edges.resize(m);
	for (int i = 0; i < m; i++) {
		cin >> edges[i].u >> edges[i].v >> edges[i].cost;
	}

	// sort edges by cost
	sort(edges.begin(), edges.end(), [](const edge &a, const edge &b) {
		return a.cost < b.cost;
	});

	// select edges to make minimum spanning tree, and get sum of cost
	int total_cost = 0;
	for (int i = 0; i < m; i++) {
		int u = find(edges[i].u, group), v = find(edges[i].v, group);
		if (u != v) {
			group[u] = v;
			total_cost += edges[i].cost;
		}
	}

	// print the total cost to make spaning tree
	cout << total_cost << endl;

	return 0;
}