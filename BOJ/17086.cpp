#include <algorithm>
#include <iostream>
#include <vector>

#define MAX_MAP_SIZE 50

enum MapCell {
	EMPTY = 0,
	SHARK = 1
};

using namespace std;

int get_distance(const pair<int, int> &p, const pair<int, int> &q) {
	int dr = abs(p.first - q.first);
	int dc = abs(p.second - q.second);

	return max(dr, dc);
}

int main(void) {
	int N, M, answer = 1;
	int map[MAX_MAP_SIZE][MAX_MAP_SIZE];

	vector<pair<int, int>> sharks;

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	// init {map} and {sharks}
	cin >> N >> M;
	for (int r = 0; r < N; r++) {
		for (int c = 0; c < M; c++) {
			cin >> map[r][c];
			if (map[r][c] == SHARK) {
				sharks.push_back({ r, c });
			}
		}
	}

	// for every empty cell
	for (int r = 0; r < N; r++) {
		for (int c = 0; c < M; c++) {
			if (map[r][c] == SHARK) continue;

			// get distance from sharks
			int min_distance = MAX_MAP_SIZE;
			for (pair<int, int> shark : sharks) {
				min_distance = min(min_distance, get_distance({ r, c }, shark));
			}

			// update the answer
			answer = max(answer, min_distance);
		}
	}

	// print the answer
	cout << answer;

	return 0;
}
