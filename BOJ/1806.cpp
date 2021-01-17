#include <algorithm>
#include <iostream>
#include <vector>

#define MAX_PARTIAL_LENGTH 100000

using namespace std;

int main(void) {
	int
		i, partial_start, // indexer
		partial_sum,
		min_partial_length,
		N, // the number of numbers
		S; // standard value

	vector<int>
		numbers;

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	// get the number of numbers and the standard value
	cin >> N >> S;
	numbers.resize(N);

	// init
	partial_start = 0;
	partial_sum = 0;
	min_partial_length = MAX_PARTIAL_LENGTH;

	// get all numbers
	for (i = 0; i < N; i++) {
		cin >> numbers[i];

		// calculate partial sum
		partial_sum += numbers[i];
		while (partial_sum >= S) {
			min_partial_length = min(min_partial_length, i - partial_start + 1);
			partial_sum -= numbers[partial_start++];
		}
	}

	// print the answer
	cout << (min_partial_length == MAX_PARTIAL_LENGTH ? 0 : min_partial_length);

	return 0;
}