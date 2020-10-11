#include <iostream>
#include <vector>

using namespace std;

double get_square_distance(int x1, int y1, int x2, int y2) {
	return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
}

int main(void) {
	int
		T, // the number of test case
		n, // the number of planetary systems
		x1, y1, x2, y2, // position coordinates
		cx, cy, r, // position coordinates and radius of a planetary system
		answer;

	vector<bool> is_in;

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	// get the number of test case
	cin >> T;
	while (T--) {
		answer = 0;
		// get start/end position
		cin >> x1 >> y1 >> x2 >> y2;

		// look for all planetary systems
		cin >> n;
		while (n--) {
			cin >> cx >> cy >> r;

			r = r * r;
			if (get_square_distance(x1, y1, cx, cy) < r
			^ get_square_distance(x2, y2, cx, cy) < r) {
				// in/out planetary system
				answer++;
			}
		}

		// print the answer
		cout << answer << '\n';
	}

	return 0;
}