#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>

#define UNKNOWN -1
#define SEA 0

using namespace std;

#define for_map(r, c, N, M) for (r = 0; r < N; r++) for (c = 0; c < M; c++)

struct Point {
	int r, c;
};

struct Bridge {
	int from, to, cost;
};

int find(vector<int> &parent, int x) {
	return (parent[x] == x) ? x : (parent[x] = find(parent, parent[x]));
}

bool is_selectable_bridge(vector<int> &parent, Bridge &bridge) {
	int x = find(parent, bridge.from);
	int y = find(parent, bridge.to);
	if (x == y) return false;
	parent[x] = y;
	return true;
}

void generate_bridge(int &prev_land, int land, int &prev_i, int i, vector<Bridge> &bridges) {
	if (i == 0) {
		// clear previous values
		prev_land = SEA;
		prev_i = 0;
	}

	// sea
	if (land == SEA) return;

	// land
	int cost = i - prev_i - 1;
	if (prev_land != SEA && land != prev_land && cost > 1) {
		// new bridge found
		bridges.emplace_back(Bridge{ prev_land, land, cost });
	}
	prev_land = land;
	prev_i = i;
}

int main() {
	int r, c, N, M;
	int n_islands = 0;
	vector<vector<int>> map;
	vector<Bridge> bridges;

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	// init map
	cin >> N >> M;
	map.resize(N, vector<int>(M));
	for_map(r, c, N, M) {
		int v;
		cin >> v;
		map[r][c] = v ? UNKNOWN : SEA;
	}

	// find all islands
	{
		int dr[] = {-1, 0, 1, 0};
		int dc[] = {0, 1, 0, -1};
		for_map(r, c, N, M) {
			if (map[r][c] != UNKNOWN) continue;

			// new island found
			map[r][c] = ++n_islands;

			queue<Point> q;
			q.push({ r, c });
			while (!q.empty()) {
				int r = q.front().r;
				int c = q.front().c;
				q.pop();

				for (int i = 0; i < 4; i++) {
					int nr = r + dr[i];
					int nc = c + dc[i];
					if (nr < 0 || nr >= N || nc < 0 || nc >= M) continue;
					if (map[nr][nc] != UNKNOWN) continue;
					map[nr][nc] = n_islands;
					q.push({ nr, nc });
				}
			}
		}
	}

	// config all edges between islands

	// horizontal edges
	{
		int i, prev_land;
		for_map(r, c, N, M) generate_bridge(prev_land, map[r][c], i, c, bridges);
	}
	// vertical edges
	{
		int i, prev_land;
		for_map(c, r, M, N) generate_bridge(prev_land, map[r][c], i, r, bridges);
	}

	// select briges with minimum cost
	int sum_cost = 0;
	{
		vector<int> parent(n_islands + 1); // index 0 is dummy
		int n_selected_bridges = 0;

		// init parent
		for (int i = n_islands; i; i--) parent[i] = i;

		// sort bridges by cost
		sort(bridges.begin(), bridges.end(), [](const Bridge &a, const Bridge &b) {
			return a.cost < b.cost;
		});

		// select bridges
		for (Bridge &bridge : bridges) {
			if (is_selectable_bridge(parent, bridge)) {
				sum_cost += bridge.cost;
				n_selected_bridges++;
			}
		}

		// check if all islands are connected
		if (n_selected_bridges != n_islands - 1) {
			sum_cost = -1;
		}
	}

	// print the answer
	cout << sum_cost;
}
