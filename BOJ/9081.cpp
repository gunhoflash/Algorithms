#include <algorithm>
#include <iostream>

using namespace std;

void print_next_word(string word) {
	int len = word.size();

	char n_alphabet[26] = { 0 };
	char max_char = 'A' - 1;

	// find substring to convert
	for (int i = len - 1; i >= 0; --i) {
		char c = word[i];
		n_alphabet[c - 'A']++;
		if (c >= max_char) {
			max_char = c;
		} else {

			// print pre-substring
			if (i > 0) {
				cout << word.substr(0, i);
			}

			// print the next alphabet
			for (int i = c - 'A' + 1; i < 26; ++i) {
				if (n_alphabet[i] != 0) {
					n_alphabet[i]--;
					cout << (char)(i + 'A');
					break;
				}
			}

			// print substring in alphabetical order
			for (int i = 0; i < 26; ++i) {
				while (n_alphabet[i]--) {
					cout << (char)(i + 'A');
				}
			}

			return;
		}
	}

	// there is no next word, print the word
	cout << word;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	// get the number of test cases
	int T;
	cin >> T;

	// do all tests
	while (T--) {
		string word;
		cin >> word;
		print_next_word(word);
		cout << endl;
	}

	return 0;
}
