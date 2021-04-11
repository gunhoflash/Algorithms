#define INF 1000000
#define EMPTY -1
#define GREEN  0
#define RED    1

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main(void) {
	int
		N, M, // size of box
		n_tomato = 0,
		day_to_all_red;

	vector<vector<int>> days_to_red;
	queue<pair<int, int>> visiting_queue;

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	// get all tomatos
	cin >> M >> N;
	days_to_red.resize(N, vector<int>(M, INF));
	for (int r = 0; r < N; r++) {
		for (int c = 0; c < M; c++) {
			int tomato;
			cin >> tomato;

			switch (tomato) {
				case EMPTY:
					days_to_red[r][c] = -1;
					break;

				case GREEN:
					days_to_red[r][c] = INF;
					n_tomato++;
					break;

				case RED:
					days_to_red[r][c] = 0;
					visiting_queue.push({ r, c });
					n_tomato++;
					break;
			}
		}
	}

	while (!visiting_queue.empty()) {
		// pop red one
		int r = visiting_queue.front().first;
		int c = visiting_queue.front().second;
		int day_to_red = day_to_all_red = days_to_red[r][c];

		visiting_queue.pop();
		n_tomato--;

		// check adjacent
		if (r > 0     && days_to_red[r - 1][c] == INF) {
			days_to_red[r - 1][c] = day_to_red + 1;
			visiting_queue.push({ r - 1, c });
		}
		if (r < N - 1 && days_to_red[r + 1][c] == INF) {
			days_to_red[r + 1][c] = day_to_red + 1;
			visiting_queue.push({ r + 1, c });
		}
		if (c > 0     && days_to_red[r][c - 1] == INF) {
			days_to_red[r][c - 1] = day_to_red + 1;
			visiting_queue.push({ r, c - 1 });
		}
		if (c < M - 1 && days_to_red[r][c + 1] == INF) {
			days_to_red[r][c + 1] = day_to_red + 1;
			visiting_queue.push({ r, c + 1 });
		}
	}

	// print the answer
	cout << (n_tomato == 0 ? day_to_all_red : -1);

	return 0;
}