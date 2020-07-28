#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>
#include <stack>
#include <string>

using namespace std;

#define DEFAULT_BELIEVE_TIME -1

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int
	N, M,
	neighbor,
	n_believers,
	from, now, believe_time,
	temp,
	i, j, size;

	pair<int, int> now_pair;

	vector<vector<int>> neighbors;
	vector<int> believe_times;
	queue<pair<int, int>> new_trust; // to, time

	// set N
	cin >> N;
	neighbors.resize(N + 1, {});
	believe_times.resize(N + 1, DEFAULT_BELIEVE_TIME);

	// set neighbors
	for (i = 0; i < N; i++) {
		while (true) {
			cin >> neighbor;
			if (neighbor == 0) break;
			neighbors[i + 1].push_back(neighbor);
		}
	}

	// make rumor
	cin >> M;
	for (i = 0; i < M; i++) {
		cin >> neighbor;
		size = neighbors[neighbor].size();
		for (j = 0; j < size; j++) {
			new_trust.push({ neighbors[neighbor][j], 1 });
		}
		believe_times[neighbor] = 0;
	}

	while (!new_trust.empty()) {

		now_pair = new_trust.front();
		now = now_pair.first;
		believe_time = now_pair.second;
		new_trust.pop();

		// check is_visited
		if (believe_times[now] >= 0) continue;

		// check near
		n_believers = 0;
		size = neighbors[now].size();
		for (i = 0; i < size; i++) {
			temp = believe_times[neighbors[now][i]];
			if (temp != DEFAULT_BELIEVE_TIME && temp < believe_time) {
				n_believers++;
			}
		}
		if (n_believers * 2 >= size) {
			// new believer
			believe_times[now] = believe_time++;
			for (i = 0; i < size; i++) {
				if (believe_times[neighbors[now][i]] == DEFAULT_BELIEVE_TIME) {
					new_trust.push({ neighbors[now][i], believe_time });
				}
			}
		}
	}

	for (i = 0; i < N; i++) {
		cout << believe_times[i + 1] << ' ';
	}

	return 0;
}