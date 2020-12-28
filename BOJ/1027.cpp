#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct Point {
	long long x;
	long long y;
};

bool is_clockwise(const Point &p1, const Point &p2, const Point &p3) {
	long long triangle_area = (
		(p1.x * p2.y + p2.x * p3.y + p3.x * p1.y)
		-
		(p2.x * p1.y + p3.x * p2.y + p1.x * p3.y)
	);

	return (triangle_area < 0);
}

int main(void) {
	int
		i, j, k, // indexers
		N, // the number of buildings
		max_n_visible; // the answer

	vector<int>
		n_visible;

	vector<Point>
		rooftop;

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	// get the number of buildings
	cin >> N;

	// init vectors
	n_visible.resize(N, 0);
	rooftop.resize(N);
	for (i = 0; i < N; i++) {
		cin >> rooftop[i].y;
		rooftop[i].x = i;
	}

	// position of buildings: i - k - j
	for (i = 0; i < N; i++) {
		for (j = i + 1; j < N; j++) {
			// check all buildings between building-{i} and building-{j}
			for (k = i + 1; k < j; k++) {
				if (j != k && !is_clockwise(rooftop[i], rooftop[j], rooftop[k])) {
					break;
				}
			}

			if (k == j) {
				// if all passed
				n_visible[i]++;
				n_visible[j]++;
			}
		}
	}

	// find maximum n_visible value
	max_n_visible = 0;
	for (i = 0; i < N; i++) {
		max_n_visible = max(max_n_visible, n_visible[i]);
	}

	// print the answer
	cout << max_n_visible;

	return 0;
}
