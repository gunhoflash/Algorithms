#include <iostream>
#include <vector>

using namespace std;

typedef int t_word;

inline t_word a2bit(const char &a) {
	return 1 << (a - 'a');
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int N, M;
	vector<t_word> words;

	t_word known_state = 0xFFFFFFFF; // 0: unknown, 1: known

	t_word n_aeiou = ~(
		a2bit('a') |
		a2bit('e') |
		a2bit('i') |
		a2bit('o') |
		a2bit('u')
	);

	cin >> N >> M;

	// init all words
	while (N--) {
		string word_string;
		cin >> word_string;

		// convert word to bit
		t_word word = 0;
		for (char &c : word_string) {
			word |= a2bit(c);
		}

		// delete vowel
		word &= n_aeiou;

		words.emplace_back(word);
	}

	// take queries
	while (M--) {
		char command, alphabet;
		cin >> command >> alphabet;

		if (command == '1') {
			// forget the alphabet
			known_state &= ~a2bit(alphabet);
		} else {
			// remember the alphabet
			known_state |= a2bit(alphabet);
		}

		// count the number of complete words
		int count = 0;
		for (t_word &word : words) {
			if ((word & known_state) == word) {
				count++;
			}
		}

		// print the number of complete words
		cout << count << '\n';
	}
}