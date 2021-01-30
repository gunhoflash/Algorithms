#define MAX_N 10
#define MAX_H 30

#include <iostream>

using namespace std;

int
	N, // the number of vertical line
	H, // the number of positions
	n_min_used_horizontal_line = 4;

bool is_horizontal_line_on[MAX_H][MAX_N] = { false };

bool is_all_matched() {
	int connection[MAX_N];

	// init connection
	for (int i = 0; i < N; i++) {
		connection[i] = i;
	}

	for (int i = 0; i < H; i++) {
		for (int j = 0; j < N - 1; j++) {
			if (is_horizontal_line_on[i][j]) {
				// swap
				int temp = connection[j];
				connection[j] = connection[j + 1];
				connection[j + 1] = temp;

				// skip next: no line next to this line
				j++;
			}
		}
	}

	// check whether all matched
	for (int i = 0; i < N; i++) {
		if (connection[i] != i) {
			return false;
		}
	}
	return true;
}

void update_min_n_horizontal_line(int n_used_horizontal_line, int h, int n) {
	// end: all matched
	if (is_all_matched()) {
		n_min_used_horizontal_line = n_used_horizontal_line;
		return;
	}

	// end: no more search
	if (n_used_horizontal_line >= n_min_used_horizontal_line - 1) return;

	// place one more line
	n_used_horizontal_line++;
	for (; h < H; h++) {
		for (; n < N - 1; n++) {
			if (is_horizontal_line_on[h][n]) {
				n++;
				continue;
			}
			if (n == N - 2 || !is_horizontal_line_on[h][n + 1]) {
				is_horizontal_line_on[h][n] = true;
				update_min_n_horizontal_line(n_used_horizontal_line, h, n + 2);
				is_horizontal_line_on[h][n] = false;
			}
		}
		n = 0;
	}
}

int main(void) {
	int M; // the number of horizontal line

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	// get data
	cin >> N >> M >> H;

	// init horizontal lines
	while (M--) {
		int a, b; // info of a horizontal line
		// set horizontal line
		cin >> a >> b;
		is_horizontal_line_on[a - 1][b - 1] = true;
	}

	// find the minimum number of additional lines to match all
	update_min_n_horizontal_line(0, 0, 0);

	// print the answer
	cout << (n_min_used_horizontal_line == 4 ? -1 : n_min_used_horizontal_line);

	return 0;
}
