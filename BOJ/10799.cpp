#include <iostream>
#include <string>

using namespace std;

int main(void) {
	int
		i, // indexer
		len, // length of a string
		n_bar, // the number of bars
		answer;
	string line;

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	// get a line of brackets
	cin >> line;
	len = line.length();

	// check all brackets from the start
	answer = 0;
	n_bar = 0;
	for (i = 0; i < len; i++) {
		if (line[i] == '(') {
			n_bar++;
		} else {
			if (line[i - 1] == '(') {
				// raser
				answer += n_bar - 1;
			} else {
				// end of a bar
				answer++;
			}
			n_bar--;
		}
	}

	// print the answer
	cout << answer;

	return 0;
}