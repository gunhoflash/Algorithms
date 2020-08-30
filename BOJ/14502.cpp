#include <iostream>
#include <vector>

#define EMPTY     0
#define WALL      1
#define VIRUS     2
#define TEMPWALL  3
#define TEMPVIRUS 4

using namespace std;

int main(void) {
	int
		r, c, w, i, j, k, // indexers
		n_empties, // the number of empty area
		n_viruses, // the number of virus area
		N, // height
		M, // width
		n_safe_area, max_n_safe_area;

	int map[64][64];

	vector<pair<int, int>> empties;
	vector<pair<int, int>> viruses;
	vector<pair<int, int>> visitings;

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	// set the map
	cin >> N >> M;
	for (r = 0; r < N; r++) {
		for (c = 0; c < M; c++) {
			cin >> i;
			switch (i) {
				case EMPTY:
					empties.push_back({ r, c });
					break;

				case VIRUS:
					viruses.push_back({ r, c });
					break;
			}
			map[r][c] = i;
		}
	}

	n_empties = empties.size();
	n_viruses = viruses.size();
	max_n_safe_area = 0;

	for (i = 0; i < n_empties; i++) {
		// select the first temp wall
		map[empties[i].first][empties[i].second] = TEMPWALL;
		for (j = i + 1; j < n_empties; j++) {
			// select the second temp wall
			map[empties[j].first][empties[j].second] = TEMPWALL;
			for (k = j + 1; k < n_empties; k++) {
				// select the third temp wall
				map[empties[k].first][empties[k].second] = TEMPWALL;

				// calculate the number of safe area

				visitings.clear();
				for (w = 0; w < n_viruses; w++) {
					visitings.push_back({ viruses[w].first, viruses[w].second });
				}

				w = 0;
				while (w < visitings.size()) {
					r = visitings[w].first;
					c = visitings[w].second;

					// check up
					if (r > 0 && map[r - 1][c] == EMPTY) {
						map[r - 1][c] = TEMPVIRUS;
						visitings.push_back({ r - 1, c });
					}
					// check down
					if (r < N - 1 && map[r + 1][c] == EMPTY) {
						map[r + 1][c] = TEMPVIRUS;
						visitings.push_back({ r + 1, c });
					}
					// check left
					if (c > 0 && map[r][c - 1] == EMPTY) {
						map[r][c - 1] = TEMPVIRUS;
						visitings.push_back({ r, c - 1 });
					}
					// check right
					if (c < M - 1 && map[r][c + 1] == EMPTY) {
						map[r][c + 1] = TEMPVIRUS;
						visitings.push_back({ r, c + 1 });
					}

					w++;
				}

				// update the maximum number of safe area
				n_safe_area = (n_empties - 3) - (visitings.size() - n_viruses);
				if (n_safe_area > max_n_safe_area) {
					max_n_safe_area = n_safe_area;
				}

				// reset the map
				for (w = n_viruses; w < visitings.size(); w++) {
					map[visitings[w].first][visitings[w].second] = EMPTY;
				}

				map[empties[k].first][empties[k].second] = EMPTY;
			}
			map[empties[j].first][empties[j].second] = EMPTY;
		}
		map[empties[i].first][empties[i].second] = EMPTY;
	}

	cout << max_n_safe_area;

	return 0;
}