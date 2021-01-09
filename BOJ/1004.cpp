#include <iostream>

using namespace std;

bool is_in_distance(int x1, int y1, int x2, int y2, int r) {
	return ((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2) < r * r);
}

int main(void) {
	int T; // the number of test case

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	// get the number of test case
	cin >> T;
	while (T--) {
		int
			n, // the number of planetary systems
			x1, y1, x2, y2, // position coordinates
			answer = 0;

		// get start/end position
		cin >> x1 >> y1 >> x2 >> y2;

		// look for all planetary systems
		cin >> n;
		while (n--) {
			int cx, cy, r; // position coordinates and radius of a planetary system

			cin >> cx >> cy >> r;

			if (is_in_distance(x1, y1, cx, cy, r) != is_in_distance(x2, y2, cx, cy, r)) {
				// in/out planetary system
				answer++;
			}
		}

		// print the answer
		cout << answer << '\n';
	}

	return 0;
}