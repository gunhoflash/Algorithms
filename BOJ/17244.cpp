#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Point {
	int r, c;
};

typedef vector<long long> Map;

int dr[] = { -1, 0, 1, 0 };
int dc[] = { 0, 1, 0, -1 };

inline void set_value_of_cell(Map& map, int r, int c) {
	map[r] |= (1LL << c);
}

inline int get_value_of_cell(Map& map, int r, int c) {
	return (map[r] >> c) & 1;
}

int get_distance(Point &from, Point &to, Map map, int n_row, int n_col) {
	queue<pair<Point, int>> q;

	q.push({from, 0});
    set_value_of_cell(map, from.r, from.c);
	while (!q.empty()) {
		Point point = q.front().first;
		int distance = q.front().second;
		q.pop();

		if (point.r == to.r && point.c == to.c) {
			// get the end point
			return distance;
		}

		// visit adjacent cells
		for (int i = 0; i < 4; i++) {
			int nr = point.r + dr[i];
			int nc = point.c + dc[i];
			if (nr < 0 || nr >= n_row || nc < 0 || nc >= n_col) {
				// out of range
				continue;
			}
			if (get_value_of_cell(map, nr, nc) == 0) {
				// not visited
				set_value_of_cell(map, nr, nc);
				q.push({ {nr, nc}, distance + 1 });
			}
		}
	}

	// should never reach here
	return 0;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int N, M, n_point;
	Map map;
	vector<Point> points;
	vector<vector<int>> distances;

	cin >> N >> M;
	map.resize(M);
	points.resize(2); // start, end

	// init map and points
	for (int r = 0; r < M; r++) {
		for (int c = 0; c < N; c++) {
			char cell;
			cin >> cell;

			switch (cell) {
			case 'S': // start
				points[0].r = r;
				points[0].c = c;
				break;
			case 'E': // end
				points[1].r = r;
				points[1].c = c;
				break;
			case 'X': // point
				points.push_back({r, c});
				break;
			case '#': // wall
				set_value_of_cell(map, r, c);
				break;
			case '.': // empty
				break;
			}
		}
	}

	// get distances for each point
	n_point = points.size();
	distances.resize(n_point, vector<int>(n_point, 0));
	for (int i = 0; i < n_point; i++) {
		for (int j = i + 1; j < n_point; j++) {
			distances[i][j] = distances[j][i] = get_distance(points[i], points[j], map, M, N);
		}
	}

	int min_distance = 0x7fffffff;
	if (n_point == 2) {
		// no points
		min_distance = distances[0][1];
	} else {
		// find the minimum distance from all routes between start and end
		vector<int> order;
		int order_size = n_point - 2;
		for (int i = 2; i < n_point; i++) {
			order.push_back(i);
		}

		do {
			int distance = 0;

			// start to first
			distance += distances[0][order[0]];

			// point to point
			for (int i = 0; i < order_size - 1; i++) {
				distance += distances[order[i]][order[i + 1]];
			}

			// last to end
			distance += distances[order[order_size - 1]][1];

			// update minimum distance
			min_distance = min(min_distance, distance);
		} while (next_permutation(order.begin(), order.end()));
	}

	cout << min_distance;
	return 0;
}
