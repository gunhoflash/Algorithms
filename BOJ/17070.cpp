#define WAY  0
#define WALL 1

#include <iostream>
#include <vector>

using namespace std;

int main(void) {
	int
		r, c, // row and column
		N; // size of the house

	vector<vector<int>>
		n_horizontal,
		n_vertical,
		n_diagonal,
		tile_type;

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	// set house
	cin >> N;
	n_horizontal.resize(N + 3, vector<int>(N + 3, 0));
	n_vertical.resize(N + 3, vector<int>(N + 3, 0));
	n_diagonal.resize(N + 3, vector<int>(N + 3, 0));

	// init all tile (way or wall)
	tile_type.resize(N + 3, vector<int>(N + 3, WALL));
	for (r = 1; r <= N; r++) {
		for (c = 1; c <= N; c++) {
			cin >> tile_type[r][c];
		}
	}

	// init n_vectors
	n_horizontal[1][1] = 1;
	for (r = 1; r <= N; r++) {
		for (c = 1; c <= N; c++) {
			// on-wall check
			if (tile_type[r][c] == WALL) {
				continue;
			}

			// horizontal
			if (tile_type[r][c + 2] == WAY) {
				// to horizontal
				n_horizontal[r][c + 1] += n_horizontal[r][c];

				// to diagonal
				if (tile_type[r + 1][c + 1] == WAY && tile_type[r + 1][c + 2] == WAY) {
					n_diagonal[r][c + 1] += n_horizontal[r][c];
				}
			}

			// vertical
			if (tile_type[r + 2][c] == WAY) {
				// to vertical
				n_vertical[r + 1][c] += n_vertical[r][c];

				// to diagonal
				if (tile_type[r + 1][c + 1] == WAY && tile_type[r + 2][c + 1] == WAY) {
					n_diagonal[r + 1][c] += n_vertical[r][c];
				}
			}

			// diagonal to horizontal
			if (tile_type[r + 1][c + 2] == WAY) {
				n_horizontal[r + 1][c + 1] += n_diagonal[r][c];
			}

			// diagonal to vertical
			if (tile_type[r + 2][c + 1] == WAY) {
				n_vertical[r + 1][c + 1] += n_diagonal[r][c];
			}

			// diagonal to diagonal
			if (tile_type[r + 1][c + 2] == WAY && tile_type[r + 2][c + 1] == WAY && tile_type[r + 2][c + 2] == WAY) {
				n_diagonal[r + 1][c + 1] += n_diagonal[r][c];
			}
		}
	}

	// print the answer
	cout <<
		n_horizontal[N][N - 1] +
		n_vertical[N - 1][N] +
		n_diagonal[N - 1][N - 1];

	return 0;
}