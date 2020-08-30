#include <iostream>
#include <queue>

using namespace std;

int seek_number_of_sections(int N, char colors[100][100]) {
	int
		i, j, // indexer
		r, c, // row and column
		n_sections; // the number of sections

	char color;
	bool visited[100][100];

	queue<pair<int, int>> visiting_queue;

	n_sections = 0;

	// init visited
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			visited[i][j] = false;
		}
	}

	// BFS
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			if (visited[i][j] == false) {
				color = colors[i][j];
				visited[i][j] = true;
				visiting_queue.push({ i, j });
				while (!visiting_queue.empty()) {
					// pop one
					r = visiting_queue.front().first;
					c = visiting_queue.front().second;
					visiting_queue.pop();

					// check up
					if (r > 0 && !visited[r - 1][c] && colors[r - 1][c] == color) {
						visited[r - 1][c] = true;
						visiting_queue.push({ r - 1, c });
					}
					// check down
					if (r < N - 1 && !visited[r + 1][c] && colors[r + 1][c] == color) {
						visited[r + 1][c] = true;
						visiting_queue.push({ r + 1, c });
					}
					// check left
					if (c > 0 && !visited[r][c - 1] && colors[r][c - 1] == color) {
						visited[r][c - 1] = true;
						visiting_queue.push({ r, c - 1 });
					}
					// check right
					if (c < N - 1 && !visited[r][c + 1] && colors[r][c + 1] == color) {
						visited[r][c + 1] = true;
						visiting_queue.push({ r, c + 1 });
					}
				}

				n_sections++;
			}
		}
	}

	return n_sections;
}

int main(void) {
	int
		i, j, // indexer
		N; // size of the grid

	char colors[100][100];

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	// set the map
	cin >> N;
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			cin >> colors[i][j];
		}
	}

	cout << seek_number_of_sections(N, colors);
	cout << ' ';

	// convert all 'G' to 'R'
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			if (colors[i][j] == 'G') {
				colors[i][j] = 'R';
			}
		}
	}

	cout << seek_number_of_sections(N, colors);

	return 0;
}