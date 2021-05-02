#include <iostream>

using namespace std;

void make_map(int map[16][16], int r_start, int c_start, int r_end, int c_end) {
	for (int r = r_start; r <= r_end; r++) {
		for (int c = c_start; c <= c_end; c++) {
			if (r == r_start || c == c_start) {
				map[r][c] = 1;
			} else {
				map[r][c] = map[r - 1][c] + map[r][c - 1];
			}
		}
	}
}

int main(void) {
	int
		N, M, K,
		answer = 1,
		r_waypoint, c_waypoint,
		map[16][16];

	cin >> N >> M >> K;

	// get location of waypoint
	if (K == 0) K = 1;
	K--;
	r_waypoint = K / M;
	c_waypoint = K % M;

	// start to waypoint
	make_map(map, 0, 0, r_waypoint, c_waypoint);
	answer *= map[r_waypoint][c_waypoint];

	// waypoint to end
	make_map(map, r_waypoint, c_waypoint, N - 1, M - 1);
	answer *= map[N - 1][M - 1];

	// print the answer
	cout << answer;

	return 0;
}