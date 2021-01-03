#include <iostream>
#include <vector>
#include <queue>

#define MAX_COST 1000000000
#define min(a, b) (a < b ? a : b)

using namespace std;

int main(void) {
	int
		i, // indexer
		N, // the number of cities
		M, // the number of buses
		from, to, cost,
		now;

	vector<bool>
		is_visited;

	vector<int>
		cost_from_start;

	vector<vector<int>>
		distance;

	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>>
		visiting_queue; // { cost from start, index }

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	// get the number of cities and buses
	cin >> N >> M;

	// init {is_visited}
	is_visited.resize(N, false);

	// init {cost}
	cost_from_start.resize(N, MAX_COST);

	// init {distance}
	distance.resize(N, vector<int>(N, MAX_COST));
	for (i = 0; i < M; i++) {
		cin >> from >> to >> cost;
		distance[from - 1][to - 1] = min(distance[from - 1][to - 1], cost);
	}

	// set start and end
	cin >> from >> to;
	cost_from_start[from - 1] = 0;

	// start
	visiting_queue.push({ 0, from - 1 });
	while (!is_visited[to - 1]) {
		// pop one
		now = visiting_queue.top().second;
		visiting_queue.pop();

		// check visited
		if (is_visited[now]) continue;
		is_visited[now] = true;

		// go next cities
		cost = cost_from_start[now];
		for (i = 0; i < N; i++) {
			if (cost + distance[now][i] < cost_from_start[i]) {
				cost_from_start[i] = cost + distance[now][i];
				visiting_queue.push({ cost_from_start[i], i });
			}
		}
	}

	// print the answer
	cout << cost_from_start[to - 1];

	return 0;
}