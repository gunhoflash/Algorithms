#include <iostream>
#include <vector>

#define EMPTY  0
#define ENEMY  1

#define max(a, b) (a > b ? a : b)

using namespace std;

struct ArcherAttack {
	int row;
	int column;
	int distance;
};

int get_distance(int r1, int c1, int r2, int c2) {
	int dr = r1 - r2;
	int dc = c1 - c2;

	if (dr < 0) dr = -dr;
	if (dc < 0) dc = -dc;

	return dr + dc;
}

int main(void) {
	int
		archer_position[3], // position of archers
		i, row, column, // indexers
		N, // the number of rows
		M, // the number of columns
		D, // maximum distance to attack
		distance,
		n_enemy_original, // the number of enemy
		max_n_enemy_attack, // the number of maximum enemy attacked
		n_enemy_passed; // the number of passed enemy

	ArcherAttack attacks[3];

	vector<vector<int>>
		map_original,
		map_test;

	// get data
	cin >> N >> M >> D;

	// init map and count enemies
	n_enemy_original = 0;
	map_original.resize(N, vector<int>(M));
	map_test.resize(N, vector<int>(M));
	for (row = 0; row < N; row++) {
		for (column = 0; column < M; column++) {
			cin >> map_original[row][column];

			if (map_original[row][column] == ENEMY)
				n_enemy_original++;
		}
	}

	// test for all possible position
	max_n_enemy_attack = 0;
	for (archer_position[0] =                      0; archer_position[0] < M; archer_position[0]++)
	for (archer_position[1] = archer_position[0] + 1; archer_position[1] < M; archer_position[1]++)
	for (archer_position[2] = archer_position[1] + 1; archer_position[2] < M; archer_position[2]++) {

		// init variables for test
		n_enemy_passed = 0;

		// init map
		for (row = 0; row < N; row++) {
			for (column = 0; column < M; column++) {
				map_test[row][column] = map_original[row][column];
			}
		}

		while (true)
		{
			// count enemy
			for (row = 0; row < N; row++) {
				for (column = 0; column < M; column++) {
					if (map_test[row][column] == ENEMY) break;
				}
				if (column != M) break;
			}
			if (row == N) break;

			// attack enemy
			attacks[0].distance = attacks[1].distance = attacks[2].distance = D + 1;
			for (row = 0; row < N; row++) {
				for (column = 0; column < M; column++) {
					if (map_test[row][column] == EMPTY) continue;

					// 3 archer test
					for (i = 0; i < 3; i++) {
						distance = get_distance(N, archer_position[i], row, column);
						if (distance > D) {
							continue;
						} else if (distance < attacks[i].distance || (distance == attacks[i].distance && column < attacks[i].column)) {
							attacks[i].row = row;
							attacks[i].column = column;
							attacks[i].distance = distance;
						}
					}
				}
			}

			// enemy down
			for (i = 0; i < 3; i++) {
				if (attacks[i].distance < D + 1) {
					map_test[attacks[i].row][attacks[i].column] = EMPTY;
				}
			}

			// enemy move
			for (column = 0; column < M; column++) {
				if (map_test[N - 1][column] == ENEMY) {
					n_enemy_passed++;
				}
			}
			for (row = N - 1; row > 0; row--) {
				for (column = 0; column < M; column++) {
					map_test[row][column] = map_test[row - 1][column];
				}
			}
			for (column = 0; column < M; column++) {
				map_test[0][column] = EMPTY;
			}

		}

		max_n_enemy_attack = max(max_n_enemy_attack, (n_enemy_original - n_enemy_passed));
	}

	cout << max_n_enemy_attack;

	return 0;
}