#include <iostream>

using namespace std;

bool is_duplicated(int *array, int last_index, int length) {
	for (int i = 0; i < length; i++) {
		if (array[last_index - i] != array[last_index - length - i]) {
			return false;
		}
	}
	return true;
}

int main(void) {
	int
		i, // indexer
		N, // length of sequence
		digit[80] = { 0 };

	// get the length of sequence
	cin >> N;

	// set each digit
	for (i = 0; i < N; i++) {
		digit[i] = (digit[i] + 1) % 4;

		// go back
		if (digit[i] == 0) {
			i -= 2;
			continue;
		}

		// check duplication
		for (int sub_len = 1; sub_len * 2 <= i + 1; sub_len++) {
			if (is_duplicated(digit, i, sub_len)) {
				// duplicated: re-try with next number
				i--;
				break;
			}
		}
	}

	// print the sequence
	for (i = 0; i < N; i++) {
		cout << digit[i];
	}

	return 0;
}