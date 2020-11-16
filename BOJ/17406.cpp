#include <iostream>
#include <vector>

#define MAX_MATRIX_VALUE 50001
#define min(a, b) (a < b ? a : b)

using namespace std;

typedef vector<vector<int>> matrix;

struct Rotation {
	int r;
	int c;
	int s;
	bool selected;
};

matrix
	m_original,
	m_rotated;

vector<Rotation *> order; // order of rotation
vector<Rotation> rotations;

// copy a matrix
void copy_matrix(matrix &from, matrix &to) {
	int
		r, c,
		N, M;

	N = from.size();
	M = from[0].size();

	for (r = 0; r < N; r++) {
		for (c = 0; c < M; c++) {
			to[r][c] = from[r][c];
		}
	}
}

void rotate_matrix(matrix &m, Rotation *rotation) {
	int
		i, // indexer
		r, c, s,
		temp;

	r = rotation->r;
	c = rotation->c;
	s = rotation->s;

	// from outer to inner
	while (s) {
		temp = m[r - s][c - s];

		// update left
		for (i = 0; i < 2 * s; i++) {
			m[r - s + i][c - s] = m[r - s + i + 1][c - s];
		}

		// update bottom
		for (i = 0; i < 2 * s; i++) {
			m[r + s][c - s + i] = m[r + s][c - s + i + 1];
		}

		// update right
		for (i = 0; i < 2 * s; i++) {
			m[r + s - i][c + s] = m[r + s - i - 1][c + s];
		}

		// update top
		for (i = 0; i < 2 * s; i++) {
			m[r - s][c + s - i] = m[r - s][c + s - i - 1];
		}

		m[r - s][c - s + 1] = temp;

		s--;
	}
}

int get_matrix_value(int N, int M) {
	int
		min_sum, sum,
		r, c;

	min_sum = MAX_MATRIX_VALUE;
	for (r = 0; r < N; r++) {
		sum = 0;
		for (c = 0; c < M; c++) {
			sum += m_rotated[r][c];
		}
		min_sum = min(min_sum, sum);
	}

	return min_sum;
}

int get_min_matrix_value(int index, int K, int N, int M) {
	int
		i, // indexer
		matrix_value, min_matrix_value;

	// end of selection
	if (index == K) {
		
		// copy matrix from the original one
		copy_matrix(m_original, m_rotated);

		// rotate
		for (i = 0; i < K; i++) {
			rotate_matrix(m_rotated, order[i]);
		}

		return get_matrix_value(N, M);
	}

	// select order[index]
	min_matrix_value = MAX_MATRIX_VALUE;
	for (i = 0; i < K; i++) {
		if (!rotations[i].selected) {
			rotations[i].selected = true;
			order[index] = &rotations[i];
			matrix_value = get_min_matrix_value(index + 1, K, N, M);
			min_matrix_value = min(min_matrix_value, matrix_value);
			rotations[i].selected = false;
		}
	}

	return min_matrix_value;
}

int main(void) {
	int
		i, // indexer
		N, M, // size of the matrix
		K, // the number of rotations
		r, c, s;

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N >> M >> K;

	// init matrix
	m_original.resize(N, vector<int>(M));
	m_rotated.resize(N, vector<int>(M));
	for (r = 0; r < N; r++) {
		for (c = 0; c < M; c++) {
			cin >> m_original[r][c];
		}
	}

	// init {order} and {selected}
	order.resize(K);
	rotations.resize(K);
	for (i = 0; i < K; i++) {
		cin >> rotations[i].r >> rotations[i].c >> rotations[i].s;
		rotations[i].r--;
		rotations[i].c--;
		rotations[i].selected = false;
	}

	cout << get_min_matrix_value(0, K, N, M);

	return 0;
}