#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

#define for_map(r, c, N) for (int r = 0; r < N; r++) for (int c = 0; c < N; c++)

int dr[] = {-1, 0, 1, 0};
int dc[] = {0, 1, 0, -1};

void clear_visit_map(vector<vector<bool>>& map, int N) {
	for_map(r, c, N) map[r][c] = false;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	vector<vector<int>> map;
	vector<vector<bool>> visited;

	int r, c, N, min_height = 100, max_height = 1;
	cin >> N;

	// init map
	map.resize(N, vector<int>(N));
	visited.resize(N, vector<bool>(N));
	for_map(r, c, N) {
		cin >> map[r][c];
		min_height = min(min_height, map[r][c]);
		max_height = max(max_height, map[r][c]);
	}

	int max_n_island = 1;
	for (int height = min_height; height < max_height; height++) {
		// count island
		int n_island = 0;
		clear_visit_map(visited, N);
		for_map(r, c, N) {
			if (map[r][c] <= height || visited[r][c]) continue;

			n_island++;

			queue<pair<int, int>> q;
			visited[r][c] = true;
			q.push({r, c});
			while (!q.empty()) {
				int r = q.front().first;
				int c = q.front().second;
				q.pop();

				for (int i = 0; i < 4; i++) {
					int nr = r + dr[i];
					int nc = c + dc[i];
					if (nr < 0 || nr >= N || nc < 0 || nc >= N) continue;
					if (map[nr][nc] <= height || visited[nr][nc]) continue;

					visited[nr][nc] = true;
					q.push({nr, nc});
				}
			}
		}

		// update max_n_island
		max_n_island = max(max_n_island, n_island);
	}

	// print the answer
	cout << max_n_island;
	return 0;
}
