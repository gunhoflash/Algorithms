#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int main(void) {

	int
		i, // indexer
		size, // size of a vector
		cost, // cost to build a building
		now, to, // building
		T, // the number of test case
		N, // the number of buildings
		K, // the number of rules for building
		D, // time to spend to build
		X, Y, // order of build
		W; // the building number to victory

	vector<vector<int>> buildings; // [[self-cost, max_cost_before, ...nexts], ...]
	vector<int> remained_n_buildings;
	queue<int> visiting_queue;

	// get data: the number of test case
	cin >> T;
	while (T--) {
		cin >> N >> K;

		// init {buildings}
		size = buildings.size();
		while (size--) buildings[size].clear();
		buildings.clear();
		buildings.resize(N + 1, vector<int>(3));

		// init {remained_n_buildings}
		remained_n_buildings.clear();
		remained_n_buildings.resize(N + 1, 0);

		// init {visiting_queue}
		size = visiting_queue.size();
		while (size--) visiting_queue.pop();

		// set cost of each building
		for (i = 1; i <= N; i++) {
			cin >> buildings[i][0];
			buildings[i][1] = 0;
		}

		// set order of build
		while (K--) {
			cin >> X >> Y;
			buildings[X].push_back(Y);
			remained_n_buildings[Y]++;
		}

		// find all starter buildings
		for (i = 1; i <= N; i++) {
			if (remained_n_buildings[i] == 0) {
				visiting_queue.push(i);
			}
		}

		// set the building number to victory
		cin >> W;
		while (true) {
			// pop one
			now = visiting_queue.front();
			cost = buildings[now][0] + buildings[now][1];
			size = buildings[now].size();
			visiting_queue.pop();

			if (now == W) {
				// complete!
				cout << cost << '\n';
				break;
			}

			for (i = 2; i < size; i++) {
				to = buildings[now][i];

				// update maximum cost for pre-construct building
				if (buildings[to][1] < cost)
					buildings[to][1] = cost;

				remained_n_buildings[to]--;
				if (remained_n_buildings[to] == 0) {
					visiting_queue.push(to);
				}
			}
		}
	}

	return 0;
}