#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

#define INT_MAX 2147483647

#define check_tile(r, c, map, visit, to_visit, fishes, t_map, distance, distance_max, shark_size) \
t_map = map[r][c];                                                                                \
if (visit[r][c] == 0) {                                                                           \
	visit[r][c] = 1;                                                                              \
	if (t_map == 0 || t_map == shark_size) {                                                      \
		/* the visitable found */                                                                 \
		to_visit.push({ distance, r, c });                                                        \
	} else if (t_map < shark_size) {                                                              \
		/* the eatable found */                                                                   \
		distance_max = distance;                                                                  \
		fishes.push_back({ r, c });                                                               \
	}                                                                                             \
}

void clear_qv(queue<vector<int>> &qv)
{
	while (!qv.empty()) {
		qv.front().clear();
		qv.pop();
	}
}

int main(void) {
	int
	i, j, // indexers
	t, t_distance, t_row, t_column, t_map, // for temporary
	time, // seconds from start
	shark_r, shark_c, shark_size, shark_ates, // data of the shark
	distance_max, // maximum distance for search
	N; // size of the map

	int map[20][20] = { 0 };
	int visit[20][20] = { 0 };

	vector<pair<int, int>> fishes; // [ row, column ]
	queue<vector<int>> to_visit; // [ distance, row, column ]

	// get data
	cin >> N;
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			cin >> t;
			map[i][j] = t;
			if (t == 9) {
				shark_r = i;
				shark_c = j;
				map[i][j] = 0;
			}
		}
	}

	// init variables
	time = 0;
	shark_size = 2;
	shark_ates = 0;

	while (true) {
		// find some near eatable fishes

		// clear and init queue
		clear_qv(to_visit);
		to_visit.push({ 0, shark_r, shark_c });

		// init visit
		for (i = 0; i < N; i++) {
			for (j = 0; j < N; j++) {
				visit[i][j] = 0;
			}
		}
		visit[shark_r][shark_c] = 1;

		// init fishes
		fishes.clear();

		// search near eatable fishes
		distance_max = INT_MAX;
		while (!to_visit.empty()) {
			// visit now
			t_distance = to_visit.front()[0];
			t_row = to_visit.front()[1];
			t_column = to_visit.front()[2];
			to_visit.pop();

			// if no more searching needed, break
			if (t_distance >= distance_max) break;

			// check nears

			// check top
			if (t_row > 0) {
				check_tile(t_row - 1, t_column, map, visit, to_visit, fishes, t_map, t_distance + 1, distance_max, shark_size)
			}

			// check left
			if (t_column > 0) {
				check_tile(t_row, t_column - 1, map, visit, to_visit, fishes, t_map, t_distance + 1, distance_max, shark_size)
			}

			// check right
			if (t_column < N - 1) {
				check_tile(t_row, t_column + 1, map, visit, to_visit, fishes, t_map, t_distance + 1, distance_max, shark_size)
			}

			// check bottom
			if (t_row < N - 1) {
				check_tile(t_row + 1, t_column, map, visit, to_visit, fishes, t_map, t_distance + 1, distance_max, shark_size)
			}
		}

		// if nothing to eat, break;
		if (fishes.size() == 0) {
			break;
		}

		// eat the fish!
		shark_ates++;
		if (shark_ates == shark_size) {
			shark_ates = 0;
			shark_size++;
		}

		// sort near eatable fishes
		sort(fishes.begin(), fishes.end());

		// shark goes to the fish
		shark_r = fishes[0].first;
		shark_c = fishes[0].second;

		// delete the fish
		map[shark_r][shark_c] = 0;

		time += distance_max;
	}

	cout << time;

	return 0;
}