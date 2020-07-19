#include <iostream>

using namespace std;

#define min(a, b) (a < b ? a : b)

int main(void) {
	int N, M, r, c, i, j, answer, W, B;
	char ch, m[50][50];

	// get input
	cin >> N >> M;
	for (i = 0; i < N; i++) {
		for (j = 0; j < M; j++) {
			do {
				cin >> ch;
			} while (ch != 'W' && ch != 'B');
			m[i][j] = ch;
		}
	}

	// full searching
	answer = 64;
	for (r = 0; r <= N - 8; r++) {
		for (c = 0; c <= M - 8; c++) {
			// check: from { r, c } to { r + 8, c + 8 }
			W = B = 0;
			for (i = 0; i < 8; i++) {
				for (j = 0; j < 8; j++) {
					ch = m[r + i][c + j];
					if ((i + j) % 2) {
						if (ch == 'W') B++;
						else W++;
					} else {
						if (ch == 'W') W++;
						else B++;
					}
				}
			}
			answer = min(answer, min(W, B));
		}
	}

	cout << answer;

	return 0;
}