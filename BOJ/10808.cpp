#include <iostream>

using namespace std;

int main(void) {
	int
		i, //indexer
		len,
		alphabets[26] = { 0 };
	string S;

	// get a string
	cin >> S;
	len = S.length();

	// count alphabets
	for (i = 0; i < len; i++) {
		alphabets[S[i] - 'a']++;
	}

	// print answer
	for (i = 0; i < 26; i++) {
		cout << alphabets[i] << ' ';
	}

	return 0;
}