#include <iostream>
#include <queue>
#include <vector>

#define TEMP 'T'
#define EMPTY '.'
#define WATER '*'
#define ROCK  'X'
#define CAVE  'D'
#define START 'S'
#define HEDGEHOG 'H'

using namespace std;

struct Point {
	int r;
	int c;
};

int dr[4] = { -1, 0, 1, 0 };
int dc[4] = { 0, -1, 0, 1 };

void water_flood(vector<vector<char>> &map, int R, int C) {
	int
		r, c;

	for (r = 1; r <= R; r++) {
		for (c = 1; c <= C; c++) {
			if (map[r][c] == EMPTY || map[r][c] == HEDGEHOG) {
				if (
					map[r - 1][c] == WATER ||
					map[r + 1][c] == WATER ||
					map[r][c - 1] == WATER ||
					map[r][c + 1] == WATER
				) {
					map[r][c] = TEMP;
				}
			}
		}
	}
	for (r = 1; r <= R; r++) {
		for (c = 1; c <= C; c++) {
			if (map[r][c] == TEMP) {
				map[r][c] = WATER;
			}
		}
	}
}

int main(void) {
	int
		R, C,
		time = 0;

	bool
		hedgehog_arrived = false;

	vector<vector<char>>
		map;

	queue<Point>
		visiting_queue,
		visiting_queue_next;

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	// init map
	cin >> R >> C;
	map.resize(R + 2, vector<char>(C + 2, ROCK));
	for (int r = 1; r <= R; r++) {
		for (int c = 1; c <= C; c++) {
			char ch;
			cin >> ch;

			// starting point found
			if (ch == START) {
				ch = HEDGEHOG;
				visiting_queue.push({ r, c });
			}

			map[r][c] = ch;
		}
	}

	// start simulation
	while (!hedgehog_arrived && !visiting_queue.empty()) {
		int r, c;

		time++;

		// water flood
		water_flood(map, R, C);

		// hedgehog move
		while (!visiting_queue.empty()) {
			// pop one
			r = visiting_queue.front().r;
			c = visiting_queue.front().c;
			visiting_queue.pop();

			// visit adjacent
			for (int i = 0; i < 4; i++) {
				if (map[r + dr[i]][c + dc[i]] == EMPTY) {
					map[r + dr[i]][c + dc[i]] = HEDGEHOG;
					visiting_queue_next.push({ r + dr[i], c + dc[i] });
				} else if (map[r + dr[i]][c + dc[i]] == CAVE) {
					// cave(end point) found
					hedgehog_arrived = true;
					break;
				}
			}
		}

		visiting_queue.swap(visiting_queue_next);
	}

	// print the answer
	if (hedgehog_arrived) {
		cout << time;
	} else {
		cout << "KAKTUS";
	}

	return 0;
}
