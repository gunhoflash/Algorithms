#include <algorithm>
#include <iostream>

using namespace std;

int main(void) {
	int
		i, j, // indexers
		N, // length of sequence
		length,
		max_length,
		sequence[1000],
		descending_length[1000],
		ascending_length[1000];

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	// get numbers
	cin >> N;
	for (i = 0; i < N; i++) {
		cin >> sequence[i];
	}

	// set ascending
	for (i = 0; i < N; i++) {
		int n = sequence[i];
		length = 1;
		for (j = 0; j < i; j++) {
			if (sequence[j] < n) {
				length = max(length, ascending_length[j] + 1);
			}
		}

		ascending_length[i] = length;
	}

	// set descending
	for (i = N - 1; i >= 0; i--) {
		int n = sequence[i];
		length = 1;
		for (j = N - 1; j > i; j--) {
			if (sequence[j] < n) {
				length = max(length, descending_length[j] + 1);
			}
		}

		descending_length[i] = length;
	}

	// find max length
	max_length = 0;
	for (i = 0; i < N; i++) {
		length = ascending_length[i] + descending_length[i] - 1;
		max_length = max(max_length, length);
	}

	// print the answer
	cout << max_length;

	return 0;
}