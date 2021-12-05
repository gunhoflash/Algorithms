#include <iostream>
#include <climits>
#include <cmath>

using namespace std;

void test() {
	// get commands
	string str;
	cin >> str;

	int
		x = 0,
		y = 0,
		min_x = 0,
		min_y = 0,
		max_x = 0,
		max_y = 0;

	// {x, y} clockwise
	int directions[4][2] = {
		{0, -1}, // up
		{1, 0}, // right
		{0, 1}, // down
		{-1, 0} // left
	};

	int direction_index = 0;

	// process all commands
	for (char c : str) {
		switch (c) {
			case 'F':
				x += directions[direction_index][0];
				y += directions[direction_index][1];
				break;
			case 'B':
				x -= directions[direction_index][0];
				y -= directions[direction_index][1];
				break;
			case 'L':
				direction_index = (direction_index + 3) % 4;
				break;
			case 'R':
				direction_index = (direction_index + 1) % 4;
				break;
		}

		// update min_x, min_y, max_x, max_y
		min_x = min(min_x, x);
		min_y = min(min_y, y);
		max_x = max(max_x, x);
		max_y = max(max_y, y);
	}

	// print the area
	cout << (max_x - min_x) * (max_y - min_y) << '\n';
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int T;
	cin >> T;
	while (T--) test();
}
