#include <iostream>
#include <queue>
#include <vector>

using namespace std;

enum TILE_TYPE {
	CHEEZE,
	INNER_AIR,
	OUTER_AIR
};

int main(void) {
	int
		temp, // for temp
		r, c, // row and column
		N, M, // size of the map
		n_cheeze,
		n_touching_air,
		time;

	vector<vector<TILE_TYPE>> tile_type;
	queue<pair<int, int>> new_outer_air;

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	n_cheeze = 0;

	// init the map
	cin >> N >> M;
	tile_type.resize(N + 2, vector<TILE_TYPE>(M + 2, OUTER_AIR));
	for (r = 1; r <= N; r++) {
		for (c = 1; c <= M; c++) {
			cin >> temp;
			if (temp == 1) {
				// cheeze
				tile_type[r][c] = CHEEZE;
				n_cheeze++;
			} else {
				// empty
				tile_type[r][c] = INNER_AIR;
			}
		}
	}

	new_outer_air.push({ 1, 1 });

	// repeat melting while cheeze exist
	time = 0;
	while (n_cheeze) {

		// check air
		while (!new_outer_air.empty()) {
			r = new_outer_air.front().first;
			c = new_outer_air.front().second;
			new_outer_air.pop();

			tile_type[r][c] = OUTER_AIR;

			// check top
			if (tile_type[r - 1][c] == INNER_AIR) {
				tile_type[r - 1][c] = OUTER_AIR;
				new_outer_air.push({ r - 1, c });
			}
			// check bottom
			if (tile_type[r + 1][c] == INNER_AIR) {
				tile_type[r + 1][c] = OUTER_AIR;
				new_outer_air.push({ r + 1, c });
			}
			// check left
			if (tile_type[r][c - 1] == INNER_AIR) {
				tile_type[r][c - 1] = OUTER_AIR;
				new_outer_air.push({ r, c - 1 });
			}
			// check right
			if (tile_type[r][c + 1] == INNER_AIR) {
				tile_type[r][c + 1] = OUTER_AIR;
				new_outer_air.push({ r, c + 1 });
			}
		}

		// melt cheeze
		for (r = 1; r <= N; r++) {
			for (c = 1; c <= M; c++) {
				if (tile_type[r][c] != CHEEZE) continue;

				n_touching_air = 0;
				if (tile_type[r - 1][c] == OUTER_AIR) n_touching_air++;
				if (tile_type[r + 1][c] == OUTER_AIR) n_touching_air++;
				if (tile_type[r][c - 1] == OUTER_AIR) n_touching_air++;
				if (tile_type[r][c + 1] == OUTER_AIR) n_touching_air++;

				// new cheeze to melt
				if (n_touching_air > 1) new_outer_air.push({ r, c });
			}
		}

		n_cheeze -= new_outer_air.size();
		time++;
	}

	// print the time to melt whole cheeze
	cout << time;

	return 0;
}