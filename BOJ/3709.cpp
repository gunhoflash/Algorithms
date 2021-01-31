#include <iostream>

#define MIRROR      1
#define VISITED     2
#define NOT_VISITED 3

using namespace std;

void laser_beam_test() {
	int
		r, c, // row and column
		n, // size of board
		n_mirror, // the number of mirrors
		direction, // 0: top, 1: right, 2: bottom, 3: left
		dr[4] = { -1, 0, 1, 0 },
		dc[4] = { 0, 1, 0, -1 },
		board[52][52][5] = { 0 }; // row/column/(empty or mirror),(direction visitied)

	// init board and set mirrors
	cin >> n >> n_mirror;
	while (n_mirror--) {
		cin >> r >> c;
		board[r][c][0] = MIRROR;
		board[r][c][1] = NOT_VISITED;
		board[r][c][2] = NOT_VISITED;
		board[r][c][3] = NOT_VISITED;
		board[r][c][4] = NOT_VISITED;
	}

	// start laser beam
	cin >> r >> c;
	     if (r == n + 1) direction = 0; // top
	else if (c ==     0) direction = 1; // right
	else if (r ==     0) direction = 2; // bottom
	else if (c == n + 1) direction = 3; // left

	while (true) {
		// go go beam
		r += dr[direction];
		c += dc[direction];

		// if out of board, end
		if (r == 0 || r == n + 1 || c == 0 || c == n + 1) {
			cout << r << ' ' << c << '\n';
			return;
		}

		// meet mirror
		if (board[r][c][0] == MIRROR) {
			if (board[r][c][1 + direction] == VISITED) {
				// infinite loop
				cout << "0 0\n";
				return;
			} else {
				// change direction
				board[r][c][1 + direction] = VISITED;
				direction = (direction + 1) % 4;
			}
		}
	}
}

int main(void) {
	int n_test;

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	// test
	cin >> n_test;
	while (n_test--) {
		laser_beam_test();
	}

	return 0;
}