#include <climits>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main(void) {
	int
		i, j, // indexers
		r, c, // position
		v,    // value of maze
		N, M; // size of the maze

	char ch;

	queue<pair<int, int>> visiting_queue;
	vector<vector<int>> maze;

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	// get data
	cin >> N >> M;
	maze.resize(N, vector<int>(M));
	for (i = 0; i < N; i++) {
		for (j = 0; j < M; j++) {
			cin >> ch;
			maze[i][j] = (ch == '1' ? INT_MAX : -1);
		}
	}

	// bfs
	maze[0][0] = 0;
	visiting_queue.push({ 0, 0 });
	while (!visiting_queue.empty()) {
		// pop one
		r = visiting_queue.front().first;
		c = visiting_queue.front().second;
		visiting_queue.pop();

		v = maze[r][c] + 1;

		if (r == N - 1 && c == M - 1) {
			// get target point
			cout << v;
			break;
		}

		// up
		if (r > 0 && maze[r - 1][c] == INT_MAX) {
			maze[r - 1][c] = v;
			visiting_queue.push({ r - 1, c });
		}

		// down
		if (r < N - 1 && maze[r + 1][c] == INT_MAX) {
			maze[r + 1][c] = v;
			visiting_queue.push({ r + 1, c });
		}

		// left
		if (c > 0 && maze[r][c - 1] == INT_MAX) {
			maze[r][c - 1] = v;
			visiting_queue.push({ r, c - 1 });
		}

		// right
		if (c < M - 1 && maze[r][c + 1] == INT_MAX) {
			maze[r][c + 1] = v;
			visiting_queue.push({ r, c + 1 });
		}
	}

	return 0;
}