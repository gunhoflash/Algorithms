#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> paper;

int number_of_negative = 0;
int number_of_zero     = 0;
int number_of_positive = 0;

void classify_paper(int r, int c, int size) {
	int i, j, type;

	type = paper[r][c];
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			if (paper[r + i][c + j] != type) {
				// not same
				size /= 3;
				classify_paper(r,            c,            size);
				classify_paper(r,            c + size,     size);
				classify_paper(r,            c + size * 2, size);
				classify_paper(r + size,     c,            size);
				classify_paper(r + size,     c + size,     size);
				classify_paper(r + size,     c + size * 2, size);
				classify_paper(r + size * 2, c,            size);
				classify_paper(r + size * 2, c + size,     size);
				classify_paper(r + size * 2, c + size * 2, size);
				return;
			}
		}
	}

	switch (type) {
		case -1: number_of_negative++; break;
		case  0: number_of_zero++;     break;
		case  1: number_of_positive++; break;
	}
}

int main(void) {
	int
		i, j, // indexers
		N; // size of paper

	// get data: N
	cin >> N;
	paper.resize(N, vector<int>(N));

	// get paper data
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			cin >> paper[i][j];
		}
	}

	// classify
	classify_paper(0, 0, N);

	// print out
	cout << number_of_negative << '\n'
		<< number_of_zero << '\n'
		<< number_of_positive << '\n';

	return 0;
}