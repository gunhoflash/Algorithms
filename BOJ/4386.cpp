#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

struct Star {
	double x;
	double y;
	Star *representative;
};

struct Edge {
	Star *a;
	Star *b;
	double cost;
};

double distance(const Star &a, const Star &b) {
	return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

Star *find_representative(Star &a) {
	return (
		a.representative == &a
		? &a
		: (a.representative = find_representative(*a.representative))
	);
}

bool unite(Star &a, Star &b) {
	Star *a_rep = find_representative(a);
	Star *b_rep = find_representative(b);
	if (a_rep != b_rep) {
		a_rep->representative = b_rep;
		return true;
	}
	return false;
}

int main() {
	vector<Star> stars;
	vector<Edge> edges;
	int n;

	// get all stars
	cin >> n;
	stars.resize(n);
	for (int i = 0; i < n; i++) {
		double x, y;
		cin >> stars[i].x >> stars[i].y;
		stars[i].representative = &stars[i];
	}

	// set all egdes
	for (int a = 0; a < n; a++) {
		for (int b = a + 1; b < n; b++) {
			edges.push_back({
				&stars[a],
				&stars[b],
				distance(stars[a], stars[b])
			});
		}
	}

	// sort all edges by distance
	sort(edges.begin(), edges.end(), [](const Edge &a, const Edge &b) {
		return a.cost < b.cost;
	});

	// select edges
	double sum_cost = 0;
	{
		int n_selected_edges = 0;
		for (const Edge &edge : edges) {
			if (!unite(*edge.a, *edge.b)) continue;
			n_selected_edges++;
			sum_cost += edge.cost;
			if (n_selected_edges == n - 1) break;
		}
	}

	// print the sum of cost
	cout << sum_cost;

	return 0;
}
