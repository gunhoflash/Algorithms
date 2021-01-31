#include <algorithm>
#include <iostream>
#include <queue>

using namespace std;

struct Point {
	int r;
	int c;
};

int main(void) {
	int
		n, m, // size of paper
		r, c, // row and column
		n_paints = 0, // the number of paints
		area, // area of a paint
		max_area = 0, // the maximum area among all paints
		paper[500][500];

	Point
		now;

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	// init paper
	cin >> n >> m;
	for (r = 0; r < n; r++) {
		for (c = 0; c < m; c++) {
			cin >> paper[r][c];
		}
	}

	// start finding all paints
	for (r = 0; r < n; r++) {
		for (c = 0; c < m; c++) {
			if (paper[r][c]) {
				// new paint found
				queue<Point>
					visiting_queue;

				n_paints++;
				area = 0;
				paper[r][c] = 0;
				visiting_queue.push({ r, c });
				while (!visiting_queue.empty()) {
					// pop one
					now = visiting_queue.front();
					visiting_queue.pop();
					area++;

					// check adjacent

					// top
					if (now.r > 0 && paper[now.r - 1][now.c]) {
						paper[now.r - 1][now.c] = 0;
						visiting_queue.push({ now.r - 1, now.c });
					}
					// bottom
					if (now.r < n - 1 && paper[now.r + 1][now.c]) {
						paper[now.r + 1][now.c] = 0;
						visiting_queue.push({ now.r + 1, now.c });
					}
					// left
					if (now.c > 0 && paper[now.r][now.c - 1]) {
						paper[now.r][now.c - 1] = 0;
						visiting_queue.push({ now.r, now.c - 1 });
					}
					// right
					if (now.c < m - 1 && paper[now.r][now.c + 1]) {
						paper[now.r][now.c + 1] = 0;
						visiting_queue.push({ now.r, now.c + 1});
					}
				}

				// update maximum area
				max_area = max(max_area, area);
			}
		}
	}

	// print the answer
	cout << n_paints << '\n' << max_area;

	return 0;
}