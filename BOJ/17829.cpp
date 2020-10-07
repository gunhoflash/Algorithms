#include <iostream>
#include <vector>

using namespace std;

// find 2nd maximum number and return
int find_second_maximum(int a, int b, int c, int d) {
	int
		ab_max, ab_min,
		cd_max, cd_min;

	if (a > b) {
		ab_max = a;
		ab_min = b;
	} else {
		ab_max = b;
		ab_min = a;
	}

	if (c > d) {
		cd_max = c;
		cd_min = d;
	} else {
		cd_max = d;
		cd_min = c;
	}

	if (ab_max > cd_max) {
		ab_max = ab_min;
	} else {
		cd_max = cd_min;
	}

	return (ab_max > cd_max ? ab_max : cd_max);
}

int main(void) {
	int
		i, j, // indexers
		N; // the size of matrix

	vector<vector<vector<int>>> matrixes;
	vector<vector<int>> *prev, *next, *temp;

	ios::sync_with_stdio(false);
	cin.tie(NULL);


	// get the size of matrix
	cin >> N;

	// init matrixes
	matrixes.resize(2, vector<vector<int>>(N, vector<int>(N)));
	prev = &matrixes[0];
	next = &matrixes[1];

	// get initial data
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			cin >> (*prev)[i][j];
		}
	}

	while (N > 1) {
		// do 222-pooling
		for (i = 0; i < N; i += 2) {
			for (j = 0; j < N; j += 2) {
				(*next)[i / 2][j / 2] = find_second_maximum(
					(*prev)[i][j],
					(*prev)[i][j + 1],
					(*prev)[i + 1][j],
					(*prev)[i + 1][j + 1]
				);
			}
		}

		// switch matrixes
		temp = prev;
		prev = next;
		next = temp;
		N /= 2;
	}

	cout << (*prev)[0][0];

	return 0;
}