#include <iostream>
#include <vector>

#define MOD 1000000000

using namespace std;

int main(void) {

	int
		i, j, // indexers
		N, // target number
		K; // dimension of decomposition

	/*
		the number of decompositions
		index: (dimension of decomposition)
	*/
	vector<vector<int>> n_decomposition;

	// get data
	cin >> N >> K;

	// init {n_decomposition}
	n_decomposition.resize(K + 1, vector<int>(N + 1));

	// init 1-decomposition
	for (i = 0; i <= N; i++) {
		n_decomposition[1][i] = 1;
	}

	// make n_decomposition from 2-decomposition
	for (i = 2; i <= K; i++) {
		n_decomposition[i][0] = 1;
		for (j = 1; j <= N; j++) {
			n_decomposition[i][j] = (n_decomposition[i][j - 1] + n_decomposition[i - 1][j]) % MOD;
		}
	}

	// print the answer
	cout << n_decomposition[K][N];

	return 0;
}