#include <iostream>
#include <map>
#include <vector>

using namespace std;

#define do_dir_lu(r, c, _do) \
while (r > 0 && c > 0) {     \
	r--; c--; _do            \
}

#define do_dir_ru(r, c, _do) \
while (r > 0 && c < N - 1) { \
	r--; c++; _do            \
}

#define do_dir_ld(r, c, _do) \
while (r < N - 1 && c > 0) { \
	r++; c--; _do            \
}

#define do_dir_rd(r, c, _do)     \
while (r < N - 1 && c < N - 1) { \
	r++; c++; _do                \
}

#define do_dir_all(i, j, r, c, _do) \
r = i; c = j;                       \
do_dir_lu(r, c, _do)                \
r = i; c = j;                       \
do_dir_ru(r, c, _do)                \
r = i; c = j;                       \
do_dir_ld(r, c, _do)                \
r = i; c = j;                       \
do_dir_rd(r, c, _do)

#define count_up(r, c) \
if (board[r][c] != 0) board[r][c]++;

#define count_down(r, c) \
if (board[r][c] != 0) board[r][c]--;

#define is_zero(r, c, b) \
if (board[r][c] != 0) b = false;

#define collect_independents(i, j, r, c, b, n)            \
for (i = 0; i < N; i++) {                                 \
	for (j = 0; j < N; j++) {                             \
		if (board[i][j] != 1) continue;                   \
		b = true;                                         \
		do_dir_all(i, j, r, c, is_zero(r, c, b))          \
		if (b) {                                          \
			/* it is independent position */              \
			board[i][j] = 0;                              \
			n++;                                          \
		}                                                 \
	}                                                     \
}

int N;
int board[10][10] = { 0 };

int count_bishops(int start_i, int start_j) {
	int i, j, r, c, count, temp;

	count = 0;

	// find all possible positions and do simulation
	i = start_i;
	j = start_j;
	for (; i < N; i++) {
		for (; j < N; j += 2) {
			if (board[i][j] != 1) continue;

			// place a bishop
			do_dir_all(i, j, r, c, count_up(r, c))
			temp = count_bishops(i, j + 2) + 1;
			count = temp > count ? temp : count;

			// remove the bishop
			do_dir_all(i, j, r, c, count_down(r, c))
		}
		if (N & 1) {
			j -= N;
		} else {
			j = N + 1 - j;
		}
	}

	return count;
}

int main(void) {
	bool b;
	int i, j, r, c, answer = 0;

	cin >> N;

	// init board
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			cin >> board[i][j];
		}
	}

	// count all independent positions
	collect_independents(i, j, r, c, b, answer);
	answer += count_bishops(0, 0);
	answer += count_bishops(0, 1);

	cout << answer;
	return 0;
}