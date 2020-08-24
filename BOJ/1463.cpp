#include <iostream>

using namespace std;

int main(void) {
	int n[1000001] = { 0 };
	int
		i, // indexer
		temp, // for temp
		N;

	// gett data: N
	cin >> N;

	n[1] = 0;
	for (i = 2; i <= N; i++) {
		temp = n[i - 1] + 1;

		// divide by 2
		if (i % 2 == 0) {
			temp = (temp > n[i / 2] + 1) ? n[i / 2] + 1 : temp;
		}

		// divide by 3
		if (i % 3 == 0) {
			temp = (temp > n[i / 3] + 1) ? n[i / 3] + 1 : temp;
		}

		n[i] = temp;
	}

	// print out the answer
	cout << n[N];

	return 0;
}