#include <iostream>

using namespace std;

int main(void) {
	int
		i, // indexer
		len, // length of string
		n_lowercase, n_uppercase, n_number, n_space; // the number of characters

	string S;
	char c;

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	// repeat N times
	while (!cin.eof()) {
		// get a string
		getline(cin, S);
		len = S.length();

		if (len == 0) break;

		// init counts
		n_lowercase = n_uppercase = n_number = n_space = 0;

		// count characters
		for (i = 0; i < len; i++) {
			c = S[i];
			     if ('a' <= c && c <= 'z') n_lowercase++;
			else if ('A' <= c && c <= 'Z') n_uppercase++;
			else if ('0' <= c && c <= '9') n_number++;
			else                           n_space++;
		}

		// print answer
		cout << n_lowercase << ' ' << n_uppercase << ' ' << n_number << ' ' << n_space << '\n';
	}

	return 0;
}