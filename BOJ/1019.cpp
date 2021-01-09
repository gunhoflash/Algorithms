#include <iostream>
#include <vector>

using namespace std;

/*

	prev_digits / digit / next_digits
	48737 / 5 / 05

*/

int main(void) {
	int
		i, // indexer
		exp10, // 10 ^ n 
		N,
		n_digit[10] = { 0 };

	// get the number
	cin >> N;

	// make ten_pow
	exp10 = 1000000000;
	while (exp10 > N) exp10 /= 10;

	// start from most significant digit (the first digit)
	while (exp10 > 0) {
		int digit = (N / exp10) % 10;
		int prev_digits = N / exp10 / 10;
		int next_digits = N % exp10;

		// (max) / digit / next_digits
		n_digit[digit] += next_digits + 1;

		// (max) / ~ (digit - 1) / next_digits
		i = (prev_digits == 0) ? 1 : 0;
		while (i < digit) {
			n_digit[i++] += exp10;
		}

		// ~ (max - 1) / * / *
		if (prev_digits > 0) {
			n_digit[0] += (prev_digits - 1) * exp10;
			for (i = 1; i < 10; i++) {
				n_digit[i] += prev_digits * exp10;
			}
		}

		exp10 /= 10;
	}

	// print the answer
	for (i = 0; i < 10; i++) {
		cout << n_digit[i] << ' ';
	}

	return 0;
}