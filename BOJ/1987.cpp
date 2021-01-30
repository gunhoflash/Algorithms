#include <iostream>
#include <stack>

#define max(a, b) (a > b ? a : b)
#define alphabet_to_mask(alphabet) (1 << (alphabet - 'A'))

using namespace std;

struct State {
	int alphabet_mask; // 0b00...DCBA
	int n_visit;
	int r;
	int c;
};

int main(void) {
	int
		R, C, // size of the board
		max_n_visit = 0; // the maximum number of visited alphabets

	char
		map[20][20];

	stack<State>
		states;

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	// init map
	cin >> R >> C;
	for (int r = 0; r < R; r++) {
		for (int c = 0; c < C; c++) {
			cin >> map[r][c];
		}
	}

	// start from (0, 0)
	states.push({
		alphabet_to_mask(map[0][0]), // alphabet_mask
		1, // n_visit
		0, // r
		0  // c
	});
	while (!states.empty()) {
		// pop one
		State now = states.top();
		states.pop();

		// update maximum
		max_n_visit = max(max_n_visit, now.n_visit);

		int
			alphabet_mask,
			n_visit = now.n_visit + 1, // the number of visited alphabets
			r       = now.r, // row
			c       = now.c; // column

		// visit top
		if (r > 0) {
			alphabet_mask = alphabet_to_mask(map[r - 1][c]);
			if ((now.alphabet_mask & alphabet_mask) == 0) {
				states.push({ now.alphabet_mask | alphabet_mask, n_visit, r - 1, c });
			}
		}
		// visit bottom
		if (r < R - 1) {
			alphabet_mask = alphabet_to_mask(map[r + 1][c]);
			if ((now.alphabet_mask & alphabet_mask) == 0) {
				states.push({ now.alphabet_mask | alphabet_mask, n_visit, r + 1, c });
			}
		}
		// visit left
		if (c > 0) {
			alphabet_mask = alphabet_to_mask(map[r][c - 1]);
			if ((now.alphabet_mask & alphabet_mask) == 0) {
				states.push({ now.alphabet_mask | alphabet_mask, n_visit, r, c - 1 });
			}
		}
		// visit right
		if (c < C - 1) {
			alphabet_mask = alphabet_to_mask(map[r][c + 1]);
			if ((now.alphabet_mask & alphabet_mask) == 0) {
				states.push({ now.alphabet_mask | alphabet_mask, n_visit, r, c + 1 });
			}
		}
	}

	// print the answer
	cout << max_n_visit;

	return 0;
}