#include <iostream>
#include <map>
#include <set>
#include <queue>

using namespace std;

// point struct
struct point {
	int x, y;
	// compare function
	bool operator<(const point &p) const {
		return x < p.x || (x == p.x && y < p.y);
	}
};

// node struct
struct node {
	bool is_valid;
	set<point> adj;
};

void register_point(point &p, map<point, node> &nodes) {
	if (nodes.find(p) == nodes.end()) {
		nodes[p] = {true, {}};
	}
}

void add_adjacency(point &p, point &q, map<point, node> &nodes) {
	nodes[p].adj.insert(q);
	nodes[q].adj.insert(p);
}

void invalidate(node &n, map<point, node> &nodes) {
	queue<point> q;

	// invalidate node
	n.is_valid = false;

	// spread validity to adjacent nodes
	for (auto &adj : n.adj) {
		q.push(adj);
	}
	while (!q.empty()) {
		point p = q.front();
		q.pop();

		if (nodes[p].is_valid == false) continue;
		nodes[p].is_valid = false;

		for (auto &adj : nodes[p].adj) {
			q.push(adj);
		}
	}
}

int main() {
	map<point, node> nodes;

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	// get all edges
	int N;
	cin >> N;
	while (N--) {
		// get an edge
		point p, q;
		cin >> p.x >> p.y >> q.x >> q.y;

		// register new nodes
		register_point(p, nodes);
		register_point(q, nodes);

		// add adjacency for each node
		add_adjacency(p, q, nodes);
	}

	// invalidate nodes which have not 2 adjacent
	for (auto &p : nodes) {
		node &n = p.second;
		if (n.adj.size() != 2) {
			// invalidate node
			invalidate(n, nodes);
		}
	}

	// count valid node groups
	int count = 0;
	for (auto &p : nodes) {
		node &n = p.second;
		if (n.is_valid) {
			// invalidate node
			invalidate(n, nodes);
			count++;
		}
	}

	// print the number of valid node groups
	cout << count;

	return 0;
}