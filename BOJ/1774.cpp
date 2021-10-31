#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

struct Point {
	double x, y;
};

struct Edge {
	int a, b;
	double cost;
};

double get_cost(const Point &a, const Point &b) {
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

int find(vector<int> &parent, int x) {
	return (parent[x] == x) ? x : (parent[x] = find(parent, parent[x]));
}

bool unite(vector<int> &parent, int a, int b) {
	a = find(parent, a);
	b = find(parent, b);
	if (a == b) return false;
	parent[a] = b;
	return true;
}

int main() {
	int N, M;
	vector<Point> points; // index 0 is dummy
	vector<Edge> edges;
	vector<int> parent; // index 0 is dummy

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N >> M;

	// get all points
	points.resize(N + 1);
	for (int i = 1; i <= N; i++) {
		cin >> points[i].x >> points[i].y;
	}

	// init parent
	parent.resize(N + 1);
	for (int i = N; i; i--) {
		parent[i] = i;
	}

	// config connections
	for (int i = 0; i < M; i++) {
		int a, b;
		cin >> a >> b;
		unite(parent, a, b);
	}

	// update parent
	for (int i = N; i; i--) {
		find(parent, i);
	}

	// make possible edges
	for (int a = 1; a <= N; a++) {
		for (int b = a + 1; b <= N; b++) {
			if (parent[a] != parent[b]) {
				edges.emplace_back(Edge{a, b, get_cost(points[a], points[b])});
			}
		}
	}

	// sort edges by cost
	sort(edges.begin(), edges.end(), [](const Edge &a, const Edge &b) {
		return a.cost < b.cost;
	});

	// select edges
	double sum_cost = 0;
	for (Edge &edge : edges) {
		if (unite(parent, edge.a, edge.b)) {
			sum_cost += edge.cost;
		}
	}

	// print result
	cout << fixed;
	cout.precision(2);
	cout << sum_cost << '\n';

	return 0;
}
