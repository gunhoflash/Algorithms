#include <iostream>
#include <map>
#include <vector>

using namespace std;

typedef map<int, long long> dictionary;

inline void update_dictionary(int key, long long value, dictionary &after) {
	dictionary::iterator it_after;

	// handle exception: invalid number
	if (key < 0 || key > 20) return;

	it_after = after.find(key);
	if (it_after == after.end()) {
		// new key
		after.insert({ key, value });
	} else {
		// exist key
		it_after->second = it_after->second + value;
	}
}

void generate_next_numbers(int n, dictionary &before, dictionary &after) {
	for (auto p : before) {
		update_dictionary(p.first + n, p.second, after);
		update_dictionary(p.first - n, p.second, after);
	}
}

int main(void) {
	vector<dictionary> possibles(2, dictionary());
	dictionary::iterator it_after;

	int
		N, // the number of data
		number, // each number
		i_before; // index of dictionary before

	// init variables
	i_before = 0;

	// get the number of data
	cin >> N;

	// take the first number
	N--;
	cin >> number;
	possibles[i_before][number] = 1;

	while (--N) {
		// config 'after'
		cin >> number;
		generate_next_numbers(number, possibles[i_before], possibles[1 - i_before]);

		// clear 'before'
		possibles[i_before].clear();

		// switch
		i_before = 1 - i_before;
	}

	// get the last number
	cin >> number;

	// find and print the answer
	it_after = possibles[i_before].find(number);
	cout << (it_after == possibles[i_before].end() ? 0 : it_after->second);

	return 0;
}