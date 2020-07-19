#include <iostream>
#include <queue>

using namespace std;

void bfs_delete(int field[50][50], int M, int N, int r, int c) {
	queue<pair<int, int>> q;
	pair<int, int> now;

	q.push({ r, c });

	while (!q.empty()) {

		// pop
		now = q.front();
		q.pop();
		r = now.first;
		c = now.second;

		// up
		if (r > 0 && field[r - 1][c] != 0) {
			field[r - 1][c] = 0;
			q.push({ r - 1, c });
		}
		// down
		if (r < N - 1 && field[r + 1][c] != 0) {
			field[r + 1][c] = 0;
			q.push({ r + 1, c });
		}
		// left
		if (c > 0 && field[r][c - 1] != 0) {
			field[r][c - 1] = 0;
			q.push({ r, c - 1 });
		}
		// right
		if (c < M - 1 && field[r][c + 1] != 0) {
			field[r][c + 1] = 0;
			q.push({ r, c + 1 });
		}
	}
}

int main(void) {
	int
		T, M, N, K, X, Y,
		i, j, field[50][50],
		answer;

	// get number of test
	cin >> T;

	while (T--) {
		// get test data
		cin >> M >> N >> K;

		// init field
		for (i = 0; i < N; i++) {
			for (j = 0; j < M; j++) {
				field[i][j] = 0;
			}
		}

		// plant cabbages
		while (K--) {
			cin >> X >> Y;
			field[Y][X] = 1;
		}

		// print the answer
		answer = 0;
		for (i = 0; i < N; i++) {
			for (j = 0; j < M; j++) {
				if (field[i][j] != 0) {
					field[i][j] = 0;
					bfs_delete(field, M, N, i, j);
					answer++;
				}
			}
		}
		cout << answer << endl;
	}

	return 0;
}