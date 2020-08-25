#include <iostream>
#include <stack>

using namespace std;

inline bool is_proper_population_gap(int gap, int L, int R) {
	if (gap < 0)
		gap *= -1;
	return (L <= gap && gap <= R);
}

int main(void) {
	int visited[52][52];
	int map[52][52];
	int union_populations[2501];
	int
		i, j, // indexer
		r, c, // row and column
		size, // size of a vector
		N, // size of the map
		L, // lower limit of the population gap between 2 countries to make a union
		R, // upper limit of the population gap between 2 countries to make a union
		n_population_shift,
		population, // population of a country
		sum_population, // population of a union
		n_not_visited;
	bool is_population_shifted;

	stack<pair<int, int>> visiting_stack;

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	// get data
	cin >> N >> L >> R;
	for (r = 1; r <= N; r++) {
		for (c = 1; c <= N; c++) {
			cin >> map[r][c];
		}
	}

	// init visited
	for (i = 0; i <= N + 1; i++) {
		visited[0][i] = -1;
		visited[i][0] = -1;
		visited[N + 1][i] = -1;
		visited[i][N + 1] = -1;
	}

	n_population_shift = 0;
	while (true) {

		// init visited
		for (r = 1; r <= N; r++) {
			for (c = 1; c <= N; c++) {
				visited[r][c] = 0;
			}
		}

		is_population_shifted = false;
		n_not_visited = N * N;
		// find a country to start making a union
		for (i = 1; i <= N; i++) {
			for (j = 1; j <= N; j++) {
				if (visited[i][j] == 0) {
					visiting_stack.push({ i, j });
					visited[i][j] = n_not_visited;

					// search adjacent countries
					size = 0;
					sum_population = 0;
					while (!visiting_stack.empty()) {
						// pop one
						r = visiting_stack.top().first;
						c = visiting_stack.top().second;
						visiting_stack.pop();
						size++;

						// count population
						population = map[r][c];
						sum_population += population;

						// check up
						if (visited[r - 1][c] == 0 && is_proper_population_gap(population - map[r - 1][c], L, R)) {
							visiting_stack.push({ r - 1, c });
							visited[r - 1][c] = n_not_visited;
						}

						// check down
						if (visited[r + 1][c] == 0 && is_proper_population_gap(population - map[r + 1][c], L, R)) {
							visiting_stack.push({ r + 1, c });
							visited[r + 1][c] = n_not_visited;
						}

						// check left
						if (visited[r][c - 1] == 0 && is_proper_population_gap(population - map[r][c - 1], L, R)) {
							visiting_stack.push({ r, c - 1 });
							visited[r][c - 1] = n_not_visited;
						}

						// check right
						if (visited[r][c + 1] == 0 && is_proper_population_gap(population - map[r][c + 1], L, R)) {
							visiting_stack.push({ r, c + 1 });
							visited[r][c + 1] = n_not_visited;
						}
					}

					// check size of the union
					if (size > 1) {
						is_population_shifted = true;
					}

					union_populations[n_not_visited] = sum_population / size;
					n_not_visited -= size;
				}
			}
		}

		// update all populations
		for (r = 1; r <= N; r++) {
			for (c = 1; c <= N; c++) {
				map[r][c] = union_populations[visited[r][c]];
			}
		}

		// after all country check
		if (is_population_shifted) {
			n_population_shift++;
		} else {
			break;
		}
	}

	// print out the answer
	cout << n_population_shift;

	return 0;
}