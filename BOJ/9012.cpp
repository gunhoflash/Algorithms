#include <iostream>
#include <string>

using namespace std;

int main(void) {
	int
		i, // indexer
		len, // length of a string
		n_left, // the number of '('
		T; // the number of test case
	string line;

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> T;
	while (T--) {
		// get a line of brackets
		cin >> line;
		len = line.length();

		// check all brackets from the start
		n_left = 0;
		for (i = 0; i < len; i++) {
			if (line[i] == '(') {
				n_left++;
			} else {
				if (n_left > 0) {
					n_left--;
				} else {
					// no more left bracket
					break;
				}
			}
		}

		// early beaked or not closed
		if (i < len || n_left > 0) {
			cout << "NO\n";
		} else {
			cout << "YES\n";
		}
	}

	return 0;
}