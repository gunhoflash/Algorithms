#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>

using namespace std;

bool compare_solution(int a, int b) {
	return abs(a) < abs(b);
}

int main(void) {
	int
		N, // the number of solutions
		min_ph = INT_MAX; // minimum absolute value of ph

	vector<int>
		solutions,
		answer(2);

	ios::sync_with_stdio(false);
	cin.tie(NULL);


	// init all solutions
	cin >> N;
	solutions.resize(N);
	for (int i = 0; i < N; i++) {
		cin >> solutions[i];
	}

	// sort solutions by absolute value
	sort(solutions.begin(), solutions.end(), compare_solution);

	// find the answer
	for (int i = 1; i < N; i++) {
		int ph = abs(solutions[i - 1] + solutions[i]);
		if (ph < min_ph) {
			// new answer found
			min_ph = ph;
			answer[0] = solutions[i - 1];
			answer[1] = solutions[i];
		}
	}

	// print the answer
	sort(answer.begin(), answer.end());
	cout << answer[0] << ' ' << answer[1];

	return 0;
}
