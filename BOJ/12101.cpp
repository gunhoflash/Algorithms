#define MAX_N 10

#include <iostream>

using namespace std;

// calculate the number of expressions that makes each value (1 ~ max)
void init_n_expressions(int *n_expressions, int max) {
	n_expressions[0] = 1;
	for (int n = 1; n <= max; n++) {
		            n_expressions[n]  = n_expressions[n - 1]; // 1 + ...
		if (n >= 2) n_expressions[n] += n_expressions[n - 2]; // 2 + ...
		if (n >= 3) n_expressions[n] += n_expressions[n - 3]; // 3 + ...
	}
}

int main(void) {
	int
		n,
		k,
		n_expressions[MAX_N + 1]; // - 1 2 4 7 13 24 44 81 149 274

	// init {n_expressions}
	init_n_expressions(n_expressions, MAX_N);

	// get {n} and {k}
	cin >> n >> k;

	// handle exception: invalid {k}
	if (k > n_expressions[n]) {
		cout << -1;
		return 0;
	}

	while (n) {
		// 3 + ...
		if (n >= 3 && k > n_expressions[n - 1] + n_expressions[n - 2]) {
			k -= n_expressions[n - 1] +  n_expressions[n - 2];
			n -= 3;
			cout << (n ? "3+" : "3");
			continue;
		}

		// 2 + ...
		if (n >= 2 && k > n_expressions[n - 1]) {
			k -= n_expressions[n - 1];
			n -= 2;
			cout << (n ? "2+" : "2");
			continue;
		}

		// 1 + ...
		n--;
		cout << (n ? "1+" : "1");
	}

	return 0;
}