#include <algorithm>
#include <iostream>

using namespace std;

long long calculate(long long a, long long b, char o) {
	switch (o) {
		case '+': return a + b;
		case '-': return a - b;
		case '*': return a * b;
		default : return 0;
	}
}

int main(void) {
	int
		N,
		n_numbers,
		numbers[10];

	char
		operators[10];

	long long
		max_before[10],
		min_before[10];

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	// get the length of formula
	cin >> N;
	n_numbers = N / 2 + 1;

	// get all numbers and operators
	cin >> numbers[0];
	for (int i = 1; i < n_numbers; i++) {
		char o, n;
		cin >> o >> n;
		operators[i - 1] = o;
		numbers[i] = n - '0';
	}

	// handle exception: only one number
	if (n_numbers == 1) {
		cout << numbers[0];
		return 0;
	}

	// init {max_before} and {min_before}
	max_before[0] = min_before[0] = numbers[0];
	max_before[1] = min_before[1] = calculate(numbers[0], numbers[1], operators[0]);

	for (int i = 2; i < n_numbers; i++) {
		char
			current_operator = operators[i - 1],
			prev_operator = operators[i - 2];

		long long
			temp_result_1, temp_result_2,
			result_of_last_bracket = calculate(numbers[i - 1], numbers[i], current_operator);

		// initialize with result without bracket
		temp_result_1 = calculate(max_before[i - 1], numbers[i], current_operator);
		temp_result_2 = calculate(min_before[i - 1], numbers[i], current_operator);
		max_before[i] = max(temp_result_1, temp_result_2);
		min_before[i] = min(temp_result_1, temp_result_2);

		// compare with using bracket
		temp_result_1 = calculate(max_before[i - 2], result_of_last_bracket, prev_operator);
		temp_result_2 = calculate(min_before[i - 2], result_of_last_bracket, prev_operator);
		max_before[i] = max(max_before[i], max(temp_result_1, temp_result_2));
		min_before[i] = min(min_before[i], min(temp_result_1, temp_result_2));
	}

	// print the answer
	cout << max_before[n_numbers - 1];

	return 0;
}