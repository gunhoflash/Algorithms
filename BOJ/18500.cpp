#include <algorithm>
#include <climits>
#include <iostream>
#include <queue>

using namespace std;

enum CaveType {
	Mineral = 'x',
	Empty = '.'
};

struct Point {
	int row;
	int column;
};

void init_2d_vector(vector<vector<char>> &v, int R, int C) {
	v.resize(R, vector<char>(C));
	for (int r = 0; r < R; r++) {
		for (int c = 0; c < C; c++) {
			cin >> v[r][c];
		}
	}
}

void print_2d_vector(vector<vector<char>> &v, int R, int C) {
	for (int r = 0; r < R; r++) {
		for (int c = 0; c < C; c++) {
			cout << v[r][c];
		}
		cout << '\n';
	}
}

void destroy_mineral(vector<vector<char>> &cave, int R, int C, bool is_left) {
	int dr[4] = { -1, 0, 1, 0 }; // up right bottom left
	int dc[4] = { 0, -1, 0, 1 }; // up right bottom left
	int visited[100][100] = { 0 }; // 0: not visited all empty, else: visited and group number

	// destroy mineral
	{
		int start = is_left ? 0 : C - 1;
		int end = is_left ? C : -1;
		int dc = is_left ? 1 : -1;
		int height;
		bool is_hit_mineral = false;

		cin >> height;
		height = R - height;

		for (int c = start; c != end; c += dc) {
			if (cave[height][c] == Mineral) {
				cave[height][c] = Empty;
				is_hit_mineral = true;
				break;
			}
		}

		// no mineral hit
		if (!is_hit_mineral) return;
	}

	int group_number = 0;
	for (int r = 0; r < R; r++) {
		for (int c = 0; c < C; c++) {
			if (visited[r][c] || cave[r][c] == Empty) continue;

			vector<Point> minerals;
			queue<Point> visiting_queue;

			// find all connected minerals
			visited[r][c] = ++group_number;
			visiting_queue.push({ r, c });
			while (!visiting_queue.empty()) {
				Point point = visiting_queue.front();
				visiting_queue.pop();
				minerals.push_back(point);

				// look adjacent
				for (int i = 0; i < 4; i++) {
					int r = point.row + dr[i];
					int c = point.column + dc[i];

					// out of range
					if (r < 0 || r > R - 1 || c < 0 || c > C - 1) continue;

					// not a mineral
					if (visited[r][c] || cave[r][c] == Empty) continue;

					// adjacent mineral found
					visited[r][c] = group_number;
					visiting_queue.push({ r, c });
				}
			}

			// calculate the height of drop
			int min_height_drop = INT_MAX;
			for (Point mineral : minerals) {
				int r = mineral.row;
				int c = mineral.column;
				int height_drop;

				while (++r < R && cave[r][c] == Empty);
				if (r == R) {
					// drop to bottom
					height_drop = R - mineral.row - 1;
				} else if (visited[r][c] != group_number) {
					// drop to other minerals
					height_drop = r - mineral.row - 1;
				} else {
					// no drop
					height_drop = INT_MAX;
				}

				min_height_drop = min(min_height_drop, height_drop);
			}

			// drop minerals
			if (min_height_drop) {
				// clear origin
				for (Point mineral : minerals) {
					int r = mineral.row;
					int c = mineral.column;
					visited[r][c] = 0;
					cave[r][c] = Empty;
				}
				// init moved locations
				for (Point mineral : minerals) {
					int r = mineral.row + min_height_drop;
					int c = mineral.column;
					visited[r][c] = group_number;
					cave[r][c] = Mineral;
				}
			}

			minerals.clear();
		}
	}
}

int main(void) {
	int
		R, C, // size of cave
		N; // the number of destruction

	bool is_left;

	vector<vector<char>> cave;

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	// init cave
	cin >> R >> C;
	init_2d_vector(cave, R, C);

	// do simulation
	is_left = true;
	cin >> N;
	while (N--) {
		destroy_mineral(cave, R, C, is_left);
		is_left = !is_left;
	}

	// print the cave
	print_2d_vector(cave, R, C);

	return 0;
}
