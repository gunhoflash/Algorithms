#include <iostream>
#include <cmath>

using namespace std;

int main(void) {
	int
		n_test, // the number of test
		m;

	double
		log_sum;

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	// do the test
	cin >> n_test;
	while (n_test--) {
		// get the number
		cin >> m;

		// calculate log10(m!)
		log_sum = 1;
		while (m) {
			log_sum += log10(m--);
		}

		// print the number of digits in m!
		cout << (int) log_sum << '\n';
	}

	return 0;
}