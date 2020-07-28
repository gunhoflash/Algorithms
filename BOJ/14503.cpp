#include <iostream>

#define NOT_CLEANED 0
#define WALL        1
#define CLEANED     2

using namespace std;

inline void go(int *r, int *c, int d) {
	switch (d) {
		case 0: *r = *r - 1; break; // north
		case 1: *c = *c + 1; break; // east
		case 2: *r = *r + 1; break; // south
		case 3: *c = *c - 1; break; // west
	}
}

inline bool is_not_cleand(int map[50][50], int r, int c, int d) {
	switch (d) {
		case 0: return (map[r - 1][c] == NOT_CLEANED); // north
		case 1: return (map[r][c + 1] == NOT_CLEANED); // east
		case 2: return (map[r + 1][c] == NOT_CLEANED); // south
		case 3: return (map[r][c - 1] == NOT_CLEANED); // west
	}
	return false;
}

inline bool is_back_wall(int map[50][50], int r, int c, int d) {
	switch (d) {
		case 0: return (map[r + 1][c] == WALL); // north
		case 1: return (map[r][c - 1] == WALL); // east
		case 2: return (map[r - 1][c] == WALL); // south
		case 3: return (map[r][c + 1] == WALL); // west
	}
	return true;
}

int main(void) {
	int
		N, M,    // size of the map
		r, c, d, // properties of the robot
		i, j,    // indexers
		answer;
	int map[50][50];

	// get data and init the robot and map
	cin >> N >> M;
	cin >> r >> c >> d;
	for (i = 0; i < N; i++) {
		for (j = 0; j < M; j++) {
			cin >> map[i][j];
		}
	}

	// go go robot!
	answer = 0;
	while (true) {
		// clean here
		if (map[r][c] == NOT_CLEANED) {
			map[r][c] = CLEANED;
			answer++;
		}

		// look around
		i = 0;
		while (i < 4) {
			d = (d + 3) % 4;
			if (is_not_cleand(map, r, c, d)) {
				break;
			}
			i++;
		}
		if (i < 4) {
			// go to clean
			go(&r, &c, d);
		} else {
			// if back is the wall, end
			if (is_back_wall(map, r, c, d)) {
				break;
			} else {
				// go back (but keep its direction)
				go(&r, &c, (d + 2) % 4);
			}
		}
	}

	cout << answer;

	return 0;
}