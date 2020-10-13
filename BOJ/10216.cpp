#include <cmath>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Circle {
	int groups;
	int x;
	int y;
	int r;
};

bool is_close(Circle &a, Circle &b) {
	int
		dx,
		dy,
		distance;

	dx       = abs(a.x - b.x);
	dy       = abs(a.y - b.y);
	distance = a.r + b.r;

	if (dx > distance || dy > distance) {
		return false;
	}

	return (distance * distance >= dx * dx + dy * dy);
}

int main(void) {
	vector<Circle> circles;
	vector<bool> visited;
	queue<int> visiting_queue;

	int
		i, j, // indexer
		now, // index of circle now visiting
		T, // the number of test case
		N, // the number of circles
		n_groups; // the number of groups

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	// get the number of test
	cin >> T;

	// do all tests
	while (T--) {
		// prepare the test
		cin >> N;
		circles.resize(N);
		visited.resize(N);
		n_groups = 0;

		// set all circles
		for (i = 0; i < N; i++) {
			cin >> circles[i].x >> circles[i].y >> circles[i].r;
			visited[i] = false;
		}

		// look for all circles
		for (i = 0; i < N; i++) {
			if (visited[i]) continue;

			// start group searching from circle-i
			n_groups++;
			visited[i] = true;
			visiting_queue.push(i);

			while (!visiting_queue.empty()) {
				// pop one
				now = visiting_queue.front();
				visiting_queue.pop();

				// find nearby circles
				for (j = 0; j < N; j++) {
					if (visited[j]) continue;

					// new close circle found
					if (is_close(circles[now], circles[j])) {
						visited[j] = true;
						visiting_queue.push(j);
					}
				}
			}
		}

		// print the number of groups
		cout << n_groups << '\n';
	}

	return 0;
}