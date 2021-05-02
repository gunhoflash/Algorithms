#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main(void) {
	int N, max_score = 0;
	vector<vector<int>> matrix;

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N;

	// init matrix
	matrix.resize(N, vector<int>(N));
	for (int r = 0; r < N; r++) {
		for (int c = 0; c < N; c++) {
			cin >> matrix[r][c];
		}
	}

	for (int r = 0; r < N; r++) {
		for (int c = 0; c < N; c++) {
			int max_step, score;

			// odd size matrix
			max_step = min(min(r + 1, c + 1), min(N - r, N - c));
			score = 0;
			for (int step = 1; step < max_step; step++) {
				score += matrix[r - step][c - step] + matrix[r + step][c + step] - matrix[r - step][c + step] - matrix[r + step][c - step];
				max_score = max(max_score, score);
			}

			// even size
			max_step = min(min(r + 1, c + 1), min(N - r, N - c) - 1);
			score = 0;
			for (int step = 0; step < max_step; step++) {
				score += matrix[r - step][c - step] + matrix[r + 1 + step][c + 1 + step] - matrix[r - step][c + 1 + step] - matrix[r + 1 + step][c - step];
				max_score = max(max_score, score);
			}
		}
	}

	// print the answer
	cout << max_score;

	return 0;
}
