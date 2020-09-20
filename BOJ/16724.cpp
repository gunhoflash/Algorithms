#include <iostream>
#include <vector>

using namespace std;

vector<vector<pair<int, int>>> parent;

pair<int, int> get_parent(pair<int, int> point) {
	pair<int, int> parent_point = parent[point.first][point.second];

	if (parent_point == point) {
		// this is root
		return point;
	} else {
		// update parent and return
		return parent[point.first][point.second] = get_parent(parent_point);
	}
}

// merge and return the size
void merge(pair<int, int> point_a, pair<int, int> point_b) {
	pair<int, int> root_a = get_parent(point_a);
	pair<int, int> root_b = get_parent(point_b);

	if (root_a != root_b) {
		// merge root_b into root_a
		parent[root_b.first][root_b.second] = root_a;
	}
}

int main(void) {
	int
		r, c, // indexers
		N, M, // size of the map
		dr, dc,
		answer;

	char ch;

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N >> M;

	// init parent
	parent.resize(N, vector<pair<int, int>>(M));
	for (r = 0; r < N; r++) {
		for (c = 0; c < M; c++) {
			parent[r][c].first = r;
			parent[r][c].second = c;
		}
	}

	// get data and update parent
	for (r = 0; r < N; r++) {
		for (c = 0; c < M; c++) {
			// get data
			cin >> ch;

			// set dr and dc
			switch (ch) {
				case 'U': dr = -1; dc =  0; break;
				case 'D': dr =  1; dc =  0; break;
				case 'L': dr =  0; dc = -1; break;
				case 'R': dr =  0; dc =  1; break;
			}

			// merge
			merge({ r, c }, { r + dr, c + dc });
		}
	}

	// count all roots
	answer = 0;
	for (r = 0; r < N; r++) {
		for (c = 0; c < M; c++) {
			if (parent[r][c].first == r && parent[r][c].second == c) {
				answer++;
			}
		}
	}

	// print the answer
	cout << answer;

	return 0;
}