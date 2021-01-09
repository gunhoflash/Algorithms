#include <iostream>
#include <queue>
#include <vector>

#define max(a, b) (a > b ? a : b)

using namespace std;

struct Building {
	int cost;
	int n_prebuild;
	int max_prebuilding_cost;
	vector<int> next;
};

int main(void) {
	int
		i, // indexer
		N; // the number of buildings

	vector<Building>
		buildings; // index 0 never being used

	queue<int>
		buildable;

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	// get the number of buildings
	cin >> N;
	buildings.resize(N + 1);

	// get all building's info
	for (i = 1; i <= N; i++) {
		cin >> buildings[i].cost;

		buildings[i].n_prebuild = 0;
		while (true) {
			int prebuild; // building's number
			cin >> prebuild;
			if (prebuild == -1) break;
			buildings[i].n_prebuild++;
			buildings[prebuild].next.push_back(i);
		}

		if (buildings[i].n_prebuild == 0) {
			// nothing needed to build
			buildable.push(i);
		}

		buildings[i].max_prebuilding_cost = 0;
	}

	// build buildings
	while (!buildable.empty()) {
		// pop one
		i = buildable.front();
		buildable.pop();

		// calculate cost to build
		int building_cost = buildings[i].max_prebuilding_cost + buildings[i].cost;

		// check next buildings
		for (auto j : buildings[i].next) {
			buildings[j].max_prebuilding_cost = max(buildings[j].max_prebuilding_cost, building_cost);

			buildings[j].n_prebuild--;
			if (buildings[j].n_prebuild == 0) {
				// nothing more needed to build
				buildable.push(j);
			}
		}
	}

	// print the answer
	for (i = 1; i <= N; i++) {
		cout << buildings[i].max_prebuilding_cost + buildings[i].cost << '\n';
	}

	return 0;
}