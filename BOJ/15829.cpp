#include <iostream>

#define r 31
#define M 1234567891

using namespace std;

int main(void) {
	int
		i, j, // indexer
		L; // length of string

	long long
		sub_hash,
		hash = 0;

	char
		ch; // alphabet

	cin >> L;
	for (i = 0; i < L; i++) {
		cin >> ch;
		sub_hash = ch - 'a' + 1;
		for (j = 0; j < i; j++) {
			sub_hash = (sub_hash * r) % M;
		}
		hash = (hash + sub_hash) % M;
	}

	// print the answer
	cout << hash;

	return 0;
}