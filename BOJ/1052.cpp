#include <iostream>

using namespace std;

int main(void) {
	int
		n_bought_bottles = 0,
		N, K;

	// set N and K
	cin >> N >> K;

	while (true) {
		int
			n_bottles = 0,
			sizeof_smallest_bottle = -1;

		for (int i = 0; i < 32; i++) {
			if ((N >> i) & 1) {
				// count the number of bottles
				n_bottles++;

				// get the size of the smallest bottle
				if (sizeof_smallest_bottle == -1) {
					sizeof_smallest_bottle = 1 << i;
				}
			}
		}

		// break the loop when the number of bottles is equals to or lower than {K}
		if (n_bottles <= K)
			break;

		// buy bottles
		n_bought_bottles += sizeof_smallest_bottle;
		N += sizeof_smallest_bottle;
	}

	// print the answer
	cout << n_bought_bottles;

	return 0;
}