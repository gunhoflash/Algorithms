#include <iostream>
#include <string>
#include <vector>

using namespace std;

void make_pattern_index(string &str, vector<int> &pi) {
	int i, matched, len;

	// init {pi}
	len = str.length();
	pi.resize(len, 0);

	i = 1;
	matched = 0;
	for (i = 1; i < len; i++) {
		while (matched > 0 && str[i] != str[matched]) {
			matched = pi[matched - 1];
		}
		if (str[i] == str[matched]) {
			matched++;
			pi[i] = matched;
		}
	}
}

int main(void) {
	int
		i, // indexer
		matched, // number of letters matched
		len_T, len_P, // length of a string
		len; // length of a vector

	string
		T, // text
		P; // pattern

	vector<int> pi;
	vector<int> found_index;

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	// get strings
	getline(cin, T);
	getline(cin, P);
	len_T = T.length();
	len_P = P.length();

	// init {pi}
	make_pattern_index(P, pi);

	// start to find the pattern
	matched = 0;
	for (i = 0; i < len_T; i++) {
		while (matched > 0 && T[i] != P[matched]) {
			matched = pi[matched - 1];
		}

		if (T[i] == P[matched]) {
			matched++;
			if (matched == len_P) {
				found_index.push_back(i - matched + 2);
				matched = pi[matched - 1];
			}
		}
	}

	// print the answer
	len = found_index.size();
	cout << len << '\n';
	for (i = 0; i < len; i++) {
		cout << found_index[i] << ' ';
	}

	return 0;
}