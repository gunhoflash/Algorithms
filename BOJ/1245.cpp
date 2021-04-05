#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Tile {
	int height = 0;
	bool is_visited = true;
};

int main(void) {
	int
		N, M, // size of the map
		n_peak = 0,
		dr[8] = { -1, -1, -1, 0, 0, 1, 1, 1 },
		dc[8] = { -1, 0, 1, -1, 1, -1, 0, 1 };

	vector<vector<Tile>>
		map;

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N >> M;

	// init map
	map.resize(N + 2, vector<Tile>(M + 2));
	for (int r = 0; r < N; r++) {
		for (int c = 0; c < M; c++) {
			int height;
			cin >> height;

			map[r + 1][c + 1].height = height;
			map[r + 1][c + 1].is_visited = height == 0;
		}
	}

	// find every peak point
	for (int r = 1; r <= N; r++) {
		for (int c = 1; c <= M; c++) {
			Tile &now = map[r][c];

			if (now.is_visited) continue;
			now.is_visited = true;

			// find group
			bool is_peak = true;
			queue<pair<int, int>> visiting_queue;
			visiting_queue.push({ r, c });
			while (!visiting_queue.empty()) {
				int r = visiting_queue.front().first;
				int c = visiting_queue.front().second;
				int height = map[r][c].height;
				visiting_queue.pop();

				for (int i = 0; i < 8; i++) {
					int adjacent_height = map[r + dr[i]][c + dc[i]].height;
					if (height == adjacent_height) {
						if (!map[r + dr[i]][c + dc[i]].is_visited) {
							map[r + dr[i]][c + dc[i]].is_visited = true;
							visiting_queue.push({ r + dr[i], c + dc[i] });
						}
					} else if (height < adjacent_height) {
						is_peak = false;
					}
				}
			}

			if (is_peak) n_peak++;
		}
	}

	// print the answer
	cout << n_peak;

	return 0;
}