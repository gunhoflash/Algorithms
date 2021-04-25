#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main(void) {
	int a, b, max_ab, gcm, lcm;
	vector<bool> is_prime;

	cin >> a >> b;

	max_ab = max(a, b);
	is_prime.resize(max_ab + 1, true);
	is_prime[0] = is_prime[1] = false;

	gcm = lcm = 1;
	for (int i = 2; i <= max_ab; i++) {
		if (!is_prime[i]) continue;
		for (int j = i * 2; j <= max_ab; j += i) {
			is_prime[j] = false;
		}

		while (true) {
			bool da = a % i == 0;
			bool db = b % i == 0;

			if (da ^ db) {
				lcm *= i;
				if (da) {
					a /= i;
				} else {
					b /= i;
				}
			} else {
				if (da) {
					gcm *= i;
					a /= i;
					b /= i;
				} else break;
			}
		}

		if (a == 1 || b == 1) {
			lcm *= a * b;
			break;
		}
	}

	cout << gcm << '\n' << gcm * lcm;

	return 0;
}