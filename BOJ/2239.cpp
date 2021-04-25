#include <iostream>
#include <stack>

using namespace std;

struct State {
	int r;
	int c;
	int n;
};

bool check(int puzzle[9][9], int r, int c, int n) {
	int row = (r / 3) * 3;
	int col = (c / 3) * 3;

	for (int i = 0; i < 9; i++) {
		if (puzzle[r][i] == n) {
			if (i != c) return false;
		}
	}
	for (int i = 0; i < 9; i++) {
		if (puzzle[i][c] == n) {
			if (i != r) return false;
		}
	}

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (puzzle[row + i][col + j] == n) {
				if (row + i != r || col + j != c) return false;
			}
		}
	}

	return true;
}

int main(void) {
	int puzzle[9][9];

	stack<State> states, remained;

	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	// init puzzle
	for (int r = 0; r < 9; r++) {
		string s;
		cin >> s;
		for (int c = 0; c < 9; c++) {
			puzzle[r][c] = s[c] - '0';
		}
	}
	for (int r = 8; r >= 0; r--) {
		for (int c = 8; c >= 0; c--) {
			if (puzzle[r][c] == 0) {
				remained.push({ r, c, 0 });
			}
		}
	}

	while (!remained.empty()) {
		State state = remained.top();
		remained.pop();


		while (true) {
			puzzle[state.r][state.c] = 0;

			if (state.n == 9) {
				state.n = 0;
				remained.push(state);
				remained.push(states.top());
				states.pop();
				break;
			}

			state.n++;
			puzzle[state.r][state.c] = state.n;
			if (check(puzzle, state.r, state.c, state.n)) {
				states.push(state);
				break;
			}
		}
	}

	for (int r = 0; r < 9; r++) {
		for (int c = 0; c < 9; c++) {
			cout << puzzle[r][c];
		}
		cout << '\n';
	}

	return 0;
}