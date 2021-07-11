#include <iostream>
#include <set>
#include <vector>

using namespace std;

#define update_max(target, value) (target = target < value ? value : target)
#define is_superset(a, b) ((a | b) == a)

vector<int> words;

int select_alphabets(int n_select, int position, int selected_bits) {
	int answer = 0;

	if (n_select == 0) {
		// check the number of supersets
		for (int word : words) {
			if (is_superset(selected_bits, word)) {
				answer++;
			}
		}
		return answer;
	}

	// select next alphabet
	for (int i = position; i <= 26 - n_select; i++) {
		int temp_answer = select_alphabets(
			n_select - 1,
			i + 1,
			selected_bits | (1 << i)
		);

		// update answer
		update_max(answer, temp_answer);
	}
	return answer;
}

int main(void) {
	int N, K;

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	// init
	cin >> N >> K;

	// init words
	for (int i = 0; i < N; i++) {
		// get a word
		string word;
		cin >> word;

		set<char> alphabet_set;
		for (char c : word) {
			alphabet_set.insert(c - 'a');
		}

		// skip: can't teach the word
		if (alphabet_set.size() > K) {
			continue;
		}

		// convert word to bits
		int bits = 0;
		for (char alphabet : alphabet_set) {
			bits |= 1 << alphabet;
		}
		words.push_back(bits);
	}

	cout << select_alphabets(K, 0, 0);

	return 0;
}
