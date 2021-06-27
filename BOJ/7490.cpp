#include <iostream>

enum Operator {
	SPACE = 0b00,
	PLUS = 0b01,
	MINUS = 0b10
};

using namespace std;

inline int get_appended_operators(int operators, int op) {
	return (operators << 2) | op;
}

inline int get_operator(int operators, int n, int N) {
	return 0b11 & (operators >> ((N - n) * 2));
}

void print_expression(int N, int operators) {
	for (int n = 1; n <= N; n++) {
		cout << n;
		int o = 0b11 & (operators >> ((N - n - 1) * 2));
		switch (o) {
			case SPACE: cout << ' '; break;
			case PLUS: cout << '+'; break;
			case MINUS: cout << '-'; break;
		}
	}
	cout << '\n';
}

int calculate(int N, int operators) {
	int
		sum = 0,
		temp = 0,
		prev_operator = PLUS;

	// append '+' to the last
	operators = get_appended_operators(operators, PLUS);

	for (int n = 1; n <= N; n++) {
		int o = get_operator(operators, n , N);
		temp = temp * 10 + n;
		if (o != SPACE) {
			sum += (prev_operator == PLUS ? temp : -temp);
			temp = 0;
			prev_operator = o;
		}
	}

	return sum;
}

void test(int N, int now, int operators) {
	if (now == N) {
		// end of selection
		if (calculate(N, operators) == 0) {
			print_expression(N, operators);
		}
		return;
	}

	// go next selection

	// whitespace
	test(N, now + 1, get_appended_operators(operators, SPACE));

	// plus
	test(N, now + 1, get_appended_operators(operators, PLUS));

	// minus
	test(N, now + 1, get_appended_operators(operators, MINUS));
}

int main(void) {
	int n_test;

	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> n_test;
	while (n_test--) {
		int N;
		cin >> N;
		test(N, 1, 0);
		cout << '\n';
	}

	return 0;
}
