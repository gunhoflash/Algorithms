#include <algorithm>
#include <iostream>
#include <climits>

using namespace std;

struct Result {
	int max_result;
	int min_result;
};

Result get_result(int *A, int last_index, int n_addition, int n_subtraction, int n_multiplication, int n_division) {
	int max_result = INT_MIN;
	int min_result = INT_MAX;

	if (last_index == 0) {
		return { A[0], A[0] };
	}

	if (n_addition) {
		Result before_result = get_result(A, last_index - 1, n_addition - 1, n_subtraction, n_multiplication, n_division);
		max_result = max(max_result, before_result.max_result + A[last_index]);
		min_result = min(min_result, before_result.min_result + A[last_index]);
	}
	if (n_subtraction) {
		Result before_result = get_result(A, last_index - 1, n_addition, n_subtraction - 1, n_multiplication, n_division);
		max_result = max(max_result, before_result.max_result - A[last_index]);
		min_result = min(min_result, before_result.min_result - A[last_index]);
	}
	if (n_multiplication) {
		Result before_result = get_result(A, last_index - 1, n_addition, n_subtraction, n_multiplication - 1, n_division);
		max_result = max(max_result, before_result.max_result * A[last_index]);
		max_result = max(max_result, before_result.min_result * A[last_index]);
		min_result = min(min_result, before_result.max_result * A[last_index]);
		min_result = min(min_result, before_result.min_result * A[last_index]);
	}
	if (n_division) {
		Result before_result = get_result(A, last_index - 1, n_addition, n_subtraction, n_multiplication, n_division - 1);
		max_result = max(max_result, before_result.max_result / A[last_index]);
		max_result = max(max_result, before_result.min_result / A[last_index]);
		min_result = min(min_result, before_result.max_result / A[last_index]);
		min_result = min(min_result, before_result.min_result / A[last_index]);
	}

	return { max_result, min_result };
}

int main(void) {
	int
		N,
		A[11],
		n_addition, n_subtraction, n_multiplication, n_division;

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N;

	// get all numbers
	for (int i = 0; i < N; i++) {
		cin >> A[i];
	}

	// get the number of each operator
	cin >> n_addition >> n_subtraction >> n_multiplication >> n_division;

	// print the answer
	Result result = get_result(A, N - 1, n_addition, n_subtraction, n_multiplication, n_division);
	cout << result.max_result << '\n' << result.min_result;

	return 0;
}