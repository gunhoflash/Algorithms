#include <iostream>
#include <queue>

#define BLANK          0
#define CHEESE         1
#define MELTING_CHEESE 2
#define VISITED_BLANK  3

#define macro_melt_or_visit(map, r, c, visiting_queue) \
	if (map[r][c] == BLANK) {                          \
		map[r][c] = VISITED_BLANK;                     \
		visiting_queue.push({ r, c });                 \
	} else if (map[r][c] == CHEESE) {                  \
		map[r][c] = MELTING_CHEESE;                    \
	}

using namespace std;

// melt the cheese and return amount of the melted
int melt_cheese(int (&map)[100][100], int width, int height) {
	int r, c, n_melted;
	queue<pair<int, int>> visiting_queue; // [[row, column], ...]

	visiting_queue.push({ 0, 0 });
	map[0][0] = VISITED_BLANK;

	// check all tiles
	while (!visiting_queue.empty()) {
		// pop
		r = visiting_queue.front().first;
		c = visiting_queue.front().second;
		visiting_queue.pop();

		// check around

		// check north
		if (r > 0)          macro_melt_or_visit(map, r - 1, c, visiting_queue);

		// check south
		if (r < height - 1) macro_melt_or_visit(map, r + 1, c, visiting_queue);

		// check west
		if (c > 0)          macro_melt_or_visit(map, r, c - 1, visiting_queue);

		// check east
		if (c < width - 1)  macro_melt_or_visit(map, r, c + 1, visiting_queue);
	}

	// melt the cheese!
	n_melted = 0;
	for (r = 0; r < height; r++) {
		for (c = 0; c < width; c++) {
			if (map[r][c] == VISITED_BLANK) {
				map[r][c] = BLANK;
			} else if (map[r][c] == MELTING_CHEESE) {
				map[r][c] = BLANK;
				n_melted++;
			}
		}
	}

	return n_melted;
}

int main(void) {
	int i, j, width, height;
	int map[100][100];
	int n_melted, n_melted_before, melting_time;

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	// get map data
	cin >> height >> width;
	for (i = 0; i < height; i++) {
		for (j = 0; j < width; j++) {
			cin >> map[i][j];
		}
	}

	melting_time = -1;
	n_melted = 0;
	do {
		// find all surface tiles of the cheeze by using BFS that starting from (0, 0)
		melting_time++;
		n_melted_before = n_melted;
		n_melted = melt_cheese(map, width, height);
	} while (n_melted != 0);

	cout << melting_time << '\n' << n_melted_before;

	return 0;
}