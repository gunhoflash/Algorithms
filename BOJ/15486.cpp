#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main(void) {
	int N;

	// index 0 never used
	vector<int> T, P, max_income_with_day_from;

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	// init vectors
	cin >> N;
	T.resize(N + 1);
	P.resize(N + 1);
	max_income_with_day_from.resize(N + 2, 0);
	for (int i = 1; i <= N; i++) {
		cin >> T[i] >> P[i];
	}

	// calculate max income backward
	for (int i = N; i > 0; i--) {
		int max_income_if_reject = max_income_with_day_from[i + 1];
		int max_income_if_take = (i + T[i] > N + 1) ? 0 : P[i] + max_income_with_day_from[i + T[i]];
		max_income_with_day_from[i] = max(max_income_if_reject, max_income_if_take);
	}

	// print the answer
	cout << max_income_with_day_from[1];

	return 0;
}
