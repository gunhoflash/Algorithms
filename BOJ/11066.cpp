#include <iostream>
#define MAX_COST 1000000000

using namespace std;

void doTest() {
	int
		K, // the number of pages
		rangeSum[500][500],
		minCost[500][500];

	// get the number of pages and each file size
	cin >> K;
	for (int i = 0; i < K; i++) {
		cin >> rangeSum[i][i];
		minCost[i][i] = 0;
	}

	// start from range 2 to {K}
	for (int rangeLength = 2; rangeLength <= K; rangeLength++) {
		for (int firstIndex = 0; firstIndex <= K - rangeLength; firstIndex++) {
			int lastIndex = firstIndex + rangeLength - 1;

			rangeSum[firstIndex][lastIndex] = rangeSum[firstIndex][lastIndex - 1] + rangeSum[lastIndex][lastIndex];
			minCost[firstIndex][lastIndex] = MAX_COST;

			// find minimum cost
			for (int i = 0; i < rangeLength - 1; i++) {
				int newCost =
					rangeSum[firstIndex][firstIndex + i] +
					minCost[firstIndex][firstIndex + i] +
					rangeSum[firstIndex + i + 1][lastIndex] +
					minCost[firstIndex + i + 1][lastIndex];

				// update minimum cost
				if (newCost < minCost[firstIndex][lastIndex]) {
					minCost[firstIndex][lastIndex] = newCost;
				}
			}
		}
	}

	// print the answer
	cout << minCost[0][K - 1] << '\n';
}

int main(void) {
	int T; // the number of test cases

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	// get the number of test cases and start all tests
	cin >> T;
	while (T--) {
		doTest();
	}

	return 0;
}
