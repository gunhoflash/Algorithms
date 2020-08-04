#include <iostream>
#include <vector>

using namespace std;

#define max(a, b) (a > b ? a : b)

int main(void) {
	int r, c, N, M, before_max;
	vector<vector<int>> candy;

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	// get data
	cin >> N >> M;
	candy.resize(N, vector<int>(M));
	for (r = 0; r < N; r++) {
		for (c = 0; c < M; c++) {
			cin >> candy[r][c];
		}
	}

	// update the maximum number of candies
	for (r = 0; r < N; r++) {
		for (c = 0; c < M; c++) {
			before_max = 0;
			if (r > 0) before_max = max(before_max, candy[r - 1][c]);
			if (c > 0) before_max = max(before_max, candy[r][c - 1]);
			candy[r][c] += before_max;
		}
	}

	cout << candy[N - 1][M - 1];
	return 0;
}