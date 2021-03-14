#include <iostream>
#include <vector>

enum BoardColor {
	White = 0,
	Red = 1,
	Blue = 2,
};

using namespace std;

struct Location {
	int row;
	int column;
};

struct Marker {
	Location location;
	int direction;
	bool at_bottom;
};

struct BoardCell {
	int color = Blue;
	vector<Marker *> markers;
};

int main(void) {
	int
		N, // size of the board
		K, // the number of markers
		turn,
		dr[4] = { 0, 0, -1, 1 }, // right, left, up, down
		dc[4] = { 1, -1, 0, 0 }; // right, left, up, down

	vector<Marker> markers;
	vector<vector<BoardCell>> board;

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N >> K;

	// set board
	board.resize(N + 2, vector<BoardCell>(N + 2));
	for (int r = 1; r <= N; r++) {
		for (int c = 1; c <= N; c++) {
			cin >> board[r][c].color;
		}
	}

	// set markers
	markers.resize(K);
	for (int i = 0; i < K; i++) {
		cin >> markers[i].location.row >> markers[i].location.column >> markers[i].direction;

		markers[i].direction--;
		markers[i].at_bottom = true;

		board[markers[i].location.row][markers[i].location.column].markers.push_back(&markers[i]);
	}

	// do simulation
	turn = 1;
	while (turn <= 1000) {
		bool end_of_game = false;
		// move markers
		for (int i = 0; i < K; i++) {
			if (!markers[i].at_bottom) continue;

			int direction;
			Location location_now, location_next;
			BoardCell *cell_now, *cell_next;

			direction = markers[i].direction;
			location_now = location_next = markers[i].location;
			location_next.row += dr[direction];
			location_next.column += dc[direction];

			cell_now = &board[location_now.row][location_now.column];
			cell_next = &board[location_next.row][location_next.column];

			if (cell_next->color == Blue) {
				// blue color: turn back
				markers[i].direction = direction = direction ^ 1;
				location_next.row += dr[direction] * 2;
				location_next.column += dc[direction] * 2;
				cell_next = &board[location_next.row][location_next.column];

				if (cell_next->color == Blue) {
					continue;
				}
			}

			// move
			if (cell_next->color == Red) {
				cell_next->markers.insert(cell_next->markers.end(), cell_now->markers.rbegin(), cell_now->markers.rend());
			} else {
				cell_next->markers.insert(cell_next->markers.end(), cell_now->markers.begin(), cell_now->markers.end());
			}
			cell_now->markers.clear();

			// set markers
			for (Marker *marker : cell_next->markers) {
				marker->at_bottom = false;
				marker->location.row = location_next.row;
				marker->location.column = location_next.column;
			}
			cell_next->markers[0]->at_bottom = true;

			end_of_game |= (cell_next->markers.size() >= 4);
		}

		if (end_of_game) break;

		turn++;
	}

	// print the answer
	cout << (turn <= 1000 ? turn : -1);

	return 0;
}