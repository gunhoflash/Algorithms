#include <iostream>
#include <vector>

using namespace std;

int main(void) {
	int
		i, j, // indexer
		n_prime, // the number of primes
		sum_prime, // sum of primes
		N,
		answer;

	vector<bool>
		is_prime;

	vector<int>
		primes;

	// get the number
	cin >> N;

	// init {is_prime}
	is_prime.resize(N + 1, true);
	is_prime[0] = is_prime[1] = false;

	// find all prime numbers based on Sieve of Eratosthenes
	for (i = 2; i <= N; i++) {
		if (!is_prime[i]) continue;

		primes.push_back(i);
		for (j = i * 2; j <= N; j += i) {
			is_prime[j] = false;
		}
	}

	answer = 0;
	n_prime = primes.size();
	for (i = 0; i < n_prime; i++) {
		// add primes from index {i}
		sum_prime = 0;
		for (j = i; j < n_prime; j++) {
			sum_prime += primes[j];

			// sum is same as the {N}
			if (sum_prime == N) {
				answer++;
				break;
			}

			// can't make {N}
			if (sum_prime > N) {
				break;
			}
		}
	}

	// print the answer
	cout << answer;

	return 0;
}