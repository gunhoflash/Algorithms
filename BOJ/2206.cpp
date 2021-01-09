#include <iostream>
#include <queue>

#define EMPTY   100000000
#define WALL    100000001
#define min(a, b) (a < b ? a : b)

using namespace std;

void calculate_distance(const pair<int, int> &start, int map[1000][1000], int N, int M) {
	queue<pair<int, int>>
		visiting_queue;

	// start searching
	map[start.first][start.second] = 1;
	visiting_queue.push({ start.first, start.second });
	while (!visiting_queue.empty()) {
		// pop one
		int r = visiting_queue.front().first;
		int c = visiting_queue.front().second;
		int path_length = map[r][c] + 1;
		visiting_queue.pop();


		// top
		if (r > 0) {
			if (map[r - 1][c] == EMPTY) {
				map[r - 1][c] = path_length;
				visiting_queue.push({ r - 1, c });
			} else if (map[r - 1][c] == WALL) {
				map[r - 1][c] = path_length;
			}
		}
		// down
		if (r < N - 1) {
			if (map[r + 1][c] == EMPTY) {
				map[r + 1][c] = path_length;
				visiting_queue.push({ r + 1, c });
			} else if (map[r + 1][c] == WALL) {
				map[r + 1][c] = path_length;
			}
		}
		// left
		if (c > 0) {
			if (map[r][c - 1] == EMPTY) {
				map[r][c - 1] = path_length;
				visiting_queue.push({ r, c - 1 });
			} else if (map[r][c - 1] == WALL) {
				map[r][c - 1] = path_length;
			}
		}
		// right
		if (c < M - 1) {
			if (map[r][c + 1] == EMPTY) {
				map[r][c + 1] = path_length;
				visiting_queue.push({ r, c + 1 });
			} else if (map[r][c + 1] == WALL) {
				map[r][c + 1] = path_length;
			}
		}
	}
}

int main(void) {
	int
		r, c, // row and column for indexer
		N, M,
		min_path_length,
		distance_from_start[1000][1000],
		distance_from_end[1000][1000];

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	// init map
	cin >> N >> M;
	for (r = 0; r < N; r++) {
		for (c = 0; c < M; c++) {
			char ch;
			cin >> ch;
			distance_from_start[r][c] = (ch == '0' ? EMPTY : WALL);
			distance_from_end[r][c]   = (ch == '0' ? EMPTY : WALL);
		}
	}

	// calculate distance from start and end
	calculate_distance({ 0, 0 }, distance_from_start, N, M);
	calculate_distance({ N - 1, M - 1 }, distance_from_end, N, M);

	// start searching
	min_path_length = distance_from_start[N - 1][M - 1];
	for (r = 0; r < N; r++) {
		for (c = 0; c < M; c++) {
			min_path_length = min(
				min_path_length,
				distance_from_start[r][c] + distance_from_end[r][c] - 1
			);
		}
	}

	// print the answer
	cout << (min_path_length < EMPTY ? min_path_length : -1);

	return 0;
}