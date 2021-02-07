#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct Tile {
	int height;
	int n_way;
	int r;
	int c;
};

bool compare_tile(const Tile &a, const Tile &b) {
	return a.height > b.height;
}

int main (void) {
	int
		r, c, // row and column
		M, N; // size of map

	vector<vector<Tile>>
		tiles;

	vector<Tile>
		visiting_vectors;

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	// set the map
	cin >> M >> N;
	tiles.resize(M, vector<Tile>(N));
	for (r = 0; r < M; r++) {
		for (c = 0; c < N; c++) {
			cin >> tiles[r][c].height;
			tiles[r][c].n_way = 0;
			tiles[r][c].r = r;
			tiles[r][c].c = c;
			visiting_vectors.push_back(tiles[r][c]);
		}
	}
	tiles[0][0].n_way = 1;

	// sort by height
	sort(visiting_vectors.begin(), visiting_vectors.end(), compare_tile);

	for (auto tile : visiting_vectors) {
		r = tile.r;
		c = tile.c;

		// top
		if (r > 0 && tiles[r - 1][c].height < tile.height) {
			tiles[r - 1][c].n_way += tiles[r][c].n_way;
		}
		// bottom
		if (r < M - 1 && tiles[r + 1][c].height < tile.height) {
			tiles[r + 1][c].n_way += tiles[r][c].n_way;
		}
		// left
		if (c > 0 && tiles[r][c - 1].height < tile.height) {
			tiles[r][c - 1].n_way += tiles[r][c].n_way;
		}
		// right
		if (c < N - 1 && tiles[r][c + 1].height < tile.height) {
			tiles[r][c + 1].n_way += tiles[r][c].n_way;
		}
	}

	// print the answer
	cout << tiles[M - 1][N - 1].n_way;

	return 0;
}