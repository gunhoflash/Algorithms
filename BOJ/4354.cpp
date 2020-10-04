#include <iostream>
#include <string>
#include <vector>

using namespace std;

int get_max_length_of_repeated_pattern(string &str) {
	int
		i,            // indexer
		matched,      // number of letters matched
		len_repeated, // length of repeated
		len;          // length of the string

	vector<int> pi;

	len = str.length();
	pi.resize(len, 0);

	// start to find the pattern
	matched = 0;
	len_repeated = 0;
	for (i = 1; i < len; i++) {
		while (matched > 0 && str[i] != str[matched]) {
			matched = pi[matched - 1];
			len_repeated = 0;
		}

		if (str[i] == str[matched]) {
			matched++;
			pi[i] = matched;
		}

		// repeated found
		if (matched * 2 == i + 1) {
			len_repeated = matched;
		}
	}

	pi.clear();
	if (len_repeated == 0) {
		// not repeated
		return 1;
	} else if (len % len_repeated != 0) {
		// not repeated
		return 1;
	} else {
		// repeated
		return len / len_repeated;
	}
}

int main(void) {
	string s;

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	while (true) {
		// get string
		cin >> s;

		// end of test case
		if (s[0] == '.') {
			break;
		}

		cout << get_max_length_of_repeated_pattern(s) << '\n';
	}

	return 0;
}