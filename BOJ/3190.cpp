#include <iostream>
#include <queue>

#define EMPTY 0
#define APPLE 1
#define SNAKE 2

using namespace std;

int main(void) {

	int map[100][100] = { EMPTY };

	// right, down, left, up
	int drs[4] = { 0, 1, 0, -1 };
	int dcs[4] = { 1, 0, -1, 0 };

	char C;
	int
		N, // size of the board
		K, // the number of apples
		L, // the number of turnning head
		X, // after {X} seconds, the snake will turn head to {C}
		r, c, // row and column
		direction, // direction (0: right, 1: down, 2: left, 3: up)
		dr, dc, // snake's moving
		time;

	deque<pair<int, int>> snake;

	// set the size of board and the number of apples
	cin >> N;
	cin >> K;

	// set position of apples
	while (K--) {
		cin >> r >> c;
		map[r - 1][c - 1] = APPLE;
	}

	// init snake
	map[0][0] = SNAKE;
	snake.push_back({ 0, 0 });
	direction = 0;
	dr = drs[direction];
	dc = dcs[direction];

	// init time
	time = 0;

	cin >> L;
	L++;
	while (L--) {
		if (L > 0) {
			cin >> X >> C;
		} else {
			X = 100000000;
		}

		// go forward
		while (time < X) {
			r = snake[0].first + dr;
			c = snake[0].second + dc;
			time++;

			// check wall collision
			if (r < 0 || r >= N || c < 0 || c >= N) {
				cout << time;
				return 0;
			}

			// check self collision
			if (map[r][c] == SNAKE) {
				cout << time;
				return 0;
			}

			// check apple
			if (map[r][c] != APPLE) {
				map[snake.back().first][snake.back().second] = EMPTY;
				snake.pop_back();
			}

			// go go snake!
			map[r][c] = SNAKE;
			snake.push_front({ r, c });
		}

		// {C} is 'L' or 'D'
		if (C == 'L') direction = (direction + 3) % 4;
		else          direction = (direction + 1) % 4;
		dr = drs[direction];
		dc = dcs[direction];
	}

	return 0;
}