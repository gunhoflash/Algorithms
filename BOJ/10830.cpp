#include <iostream>
#include <vector>

using namespace std;

typedef vector<int> row;
typedef vector<row> matrix;
typedef unsigned long long ull;

matrix multiply_matrix(const matrix &A, const matrix &B) {
	int N = A.size();
	matrix AB;

	AB.resize(N, row(N, 0));
	for (int r = 0; r < N; r++) {
		for (int c = 0; c < N; c++) {
			for (int i = 0; i < N; i++) {
				AB[r][c] += A[r][i] * B[i][c];
			}
			AB[r][c] %= 1000;
		}
	}

	return AB;
}

matrix square_matrix(const matrix &M, const ull P) {
	if (P == 1) return M;
	if (P & 1) return multiply_matrix(square_matrix(multiply_matrix(M, M), P / 2), M);
	return square_matrix(multiply_matrix(M, M), P / 2);
}

int main(void) {
	int N;
	ull B;
	matrix A, answer;

	cin >> N >> B;

	// init the matrix
	A.resize(N, row(N));
	for (int r = 0; r < N; r++) {
		for (int c = 0; c < N; c++) {
			cin >> A[r][c];
		}
	}

	// get the matrix A^B
	answer = square_matrix(A, B);

	// print the answer
	for (int r = 0; r < N; r++) {
		for (int c = 0; c < N; c++) {
			cout << answer[r][c] % 1000 << ' ';
		}
		cout << '\n';
	}

	return 0;
}
