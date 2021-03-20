#include <algorithm>
#include <iostream>
#include <climits>

using namespace std;

struct MinMax {
	long long max;
	long long min;
};

MinMax get_min_max(char expression[], int length) {
	if (length == 1) {
		return {
			expression[0] - '0',
			expression[0] - '0'
		};
	}

	// divide by every operator
	MinMax result = { LLONG_MIN, LLONG_MAX };
	for (int i = 1; i < length - 1; i += 2) {
		MinMax left_result = get_min_max(expression, i);
		MinMax right_result = get_min_max(expression + i + 1, length - i - 1);

		switch (expression[i]) {
			case '+':
			result.max = max(result.max, left_result.max + right_result.max);
			result.min = min(result.min, left_result.min + right_result.min);
			break;

			case '-':
			result.max = max(result.max, left_result.max - right_result.min);
			result.min = min(result.min, left_result.min - right_result.max);
			break;

			case '*':
			result.max = max(result.max, left_result.max * right_result.max);
			result.max = max(result.max, left_result.max * right_result.min);
			result.max = max(result.max, left_result.min * right_result.max);
			result.max = max(result.max, left_result.min * right_result.min);

			result.min = min(result.min, left_result.max * right_result.max);
			result.min = min(result.min, left_result.max * right_result.min);
			result.min = min(result.min, left_result.min * right_result.max);
			result.min = min(result.min, left_result.min * right_result.min);
			break;
		}
	}

	return result;
}

int main(void) {
	int N;
	char expression[19];

	cin >> N >> expression;

	cout << get_min_max(expression, N).max;

	return 0;
}