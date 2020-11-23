#include <iostream>
#include <vector>
#include <stack>

#define NO_GROUP -1

using namespace std;

int main(void) {
	int
		i, j, // indexers
		now, // now visiting city
		group,
		N, // the number of cities
		M; // length of trip

	bool
		trip_available;

	vector<int> city_group;
	vector<vector<int>> is_connected;
	stack<int> visiting_stack; // for DFS

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	// get the number of cities
	cin >> N;

	// get length of trip
	cin >> M;

	// init {city_group}
	city_group.resize(N, NO_GROUP);

	// init {is_connected}
	is_connected.resize(N, vector<int>(N));
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			cin >> is_connected[i][j];
		}
	}

	// unite cities using DFS
	for (i = 0; i < N; i++) {
		if (city_group[i] == NO_GROUP) {
			city_group[i] = i;

			// DFS to unite connected cities
			visiting_stack.push(i);
			while (!visiting_stack.empty()) {
				// pop one
				now = visiting_stack.top();
				visiting_stack.pop();

				// check adjacent
				for (j = 0; j < N; j++) {
					if (is_connected[now][j] && city_group[j] == NO_GROUP) {
						city_group[j] = i;
						visiting_stack.push(j);
					}
				}
			}
		}
	}

	// check trip available
	trip_available = true;

	// get the first city
	cin >> now;
	group = city_group[now - 1];

	// get next cities
	while (--M) {
		cin >> now;

		if (group != city_group[now - 1]) {
			// other group
			trip_available = false;
			break;
		}
	}

	cout << (trip_available ? "YES" : "NO");

	return 0;
}