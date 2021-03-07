#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>

using namespace std;

int main(void) {
	int
		N, // the size of array
		min_before, max_after,
		answer;

	vector<int>
		numbers,
		left_max,
		right_max;

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	// init vectors
	cin >> N;
	numbers.resize(N);
	left_max.resize(N);
	right_max.resize(N);

	// get all numbers
	for (int i = 0; i < N; i++) {
		cin >> numbers[i];
	}

	// calculate left part
	min_before = numbers[0];
	left_max[0] = INT_MIN;
	for (int i = 1; i < N - 2; i++) {
		left_max[i] = max(left_max[i - 1], numbers[i] - min_before);

		// update minimum
		min_before = min(min_before, numbers[i]);
	}

	// calculate right part
	max_after = numbers[N - 1];
	right_max[N - 1] = INT_MIN;
	for (int i = N - 2; i > 1; i--) {
		right_max[i] = max(right_max[i + 1], max_after - numbers[i]);

		// update maximum
		max_after = max(max_after, numbers[i]);
	}

	// get the answer
	answer = INT_MIN;
	for (int i = 1; i < N - 2; i++) {
		answer = max(answer, left_max[i] + right_max[i + 1]);
	}

	// print the answer
	cout << answer;

	return 0;
}