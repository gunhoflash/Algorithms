#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

/*

	Struct Declarations

*/

typedef struct {
	int x;
	int y;
	int z;
	int parent;
} Planet;

typedef struct {
	long long cost;
	int p;
	int q;
} Tunnel;

/*

	Functions for Planet

*/

long long get_cost(Planet &p, Planet &q) {
	long long dx = p.x - q.x;
	long long dy = p.y - q.y;
	long long dz = p.z - q.z;

	// abs
	if (dx < 0) dx = -dx;
	if (dy < 0) dy = -dy;
	if (dz < 0) dz = -dz;

	// make dx smallest
	if (dy < dx) dx = dy;
	if (dz < dx) dx = dz;
	return dx;
}

int get_parent(int n, vector<Planet> &planets) {
	if (planets[n].parent == n) {
		return n;
	} else {
		return planets[n].parent = get_parent(planets[n].parent, planets);
	}
}

bool merge(int p, int q, vector<Planet> &planets) {
	int root_p = get_parent(p, planets);
	int root_q = get_parent(q, planets);

	if (root_p == root_q) {
		// already merged
		return false;
	}

	// merge
	planets[root_q].parent = root_p;
	return true;
}

/*

	Functions for Tunnel

*/

// compare tunnels
bool compare_tunnel(Tunnel p, Tunnel q) {
	return p.cost < q.cost;
}

/*

	main

*/

int main(void) {
	vector<Planet> planets;
	vector<Tunnel> tunnels;
	vector<pair<int, int>> x_order, y_order, z_order; // < coordinate, index >

	int
		i, // indexer
		x, y, z, // coordinates of a planet
		p, q, // index of planets
		t, // the number of used tunnels
		T, // the number of all tunnels
		N; // the number of planets

	long long
		cost,
		total_cost;

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	// get the number of planets
	cin >> N;

	// init vectors
	planets.resize(N);
	x_order.resize(N);
	y_order.resize(N);
	z_order.resize(N);

	// set all planets
	for (i = 0; i < N; i++) {
		cin >> x >> y >> z;
		planets[i].x = x;
		planets[i].y = y;
		planets[i].z = z;
		planets[i].parent = i;

		x_order[i].first = x;
		x_order[i].second = i;

		y_order[i].first = y;
		y_order[i].second = i;

		z_order[i].first = z;
		z_order[i].second = i;
	}

	// sort vectors
	sort(x_order.begin(), x_order.end());
	sort(y_order.begin(), y_order.end());
	sort(z_order.begin(), z_order.end());

	// make tunnels
	for (i = 0; i < N - 1; i++) {
		p    = x_order[i].second;
		q    = x_order[i + 1].second;
		cost = get_cost(planets[p], planets[q]);
		tunnels.push_back({ cost, p, q });

		p    = y_order[i].second;
		q    = y_order[i + 1].second;
		cost = get_cost(planets[p], planets[q]);
		tunnels.push_back({ cost, p, q });

		p    = z_order[i].second;
		q    = z_order[i + 1].second;
		cost = get_cost(planets[p], planets[q]);
		tunnels.push_back({ cost, p, q });
	}

	// sort tunnels by distance
	sort(tunnels.begin(), tunnels.end(), compare_tunnel);

	// look for minimum distance tunnels
	total_cost = 0;
	t = 0;
	T = tunnels.size();
	for (i = 0; i < T; i++) {

		cost = tunnels[i].cost;
		p    = tunnels[i].p;
		q    = tunnels[i].q;

		if (merge(p, q, planets)) {
			total_cost += cost;

			// early break when enough number of tunnels
			if (++t == N - 1) break;
		}
	}

	// print the answer
	cout << total_cost;

	return 0;
}