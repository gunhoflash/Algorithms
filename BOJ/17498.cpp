#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>

using namespace std;

struct Cell {
	int max_sum_score_bofore; // default: 0(at the first row) or INT_MIN
	int score;
};

int main(void) {
	int N, M, D;
	vector<vector<Cell>> cell;

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N >> M >> D;

	// init every cell
	cell.resize(N + D, vector<Cell>(M));
	for (int row = 0; row < N; row++) {
		for (int col = 0; col < M; col++) {
			cin >> cell[row][col].score;
			cell[row][col].max_sum_score_bofore = row ? INT_MIN : 0;
		}
	}

	// calculate max_sum_score_bofore for each cell
	for (int row = 0; row < N; row++) {
		for (int col = 0; col < M; col++) {
			// for each cell

			// check all next cells
			for (int next_row = row + 1; next_row <= row + D; next_row++) {
				int max_col_gap = D - (next_row - row); // D - row_gap
				for (int next_col = max(col - max_col_gap, 0); next_col < min(M, col + max_col_gap + 1); next_col++) {
					// update max_sum_score_bofore of next cell
					Cell &now = cell[row][col];
					Cell &next = cell[next_row][next_col];
					next.max_sum_score_bofore = max(next.max_sum_score_bofore, now.max_sum_score_bofore + now.score * next.score);
				}
			}
		}
	}

	// print the answer
	int answer = INT_MIN;
	for (int col = 0; col < M; col++) {
		answer = max(answer, cell[N - 1][col].max_sum_score_bofore);
	}
	cout << answer;

	return 0;
}