#include <iostream>
#include <vector>

using namespace std;

int last_card(vector<int> &prevs) {
	int
		i, // indexer
		size; // the number of cards

	vector<int> nexts;

	// remove some cards
	size = prevs.size();
	if (size % 2 == 1) {
		nexts.push_back(prevs[size - 1]);
	}
	for (i = 1; i < size; i += 2) {
		nexts.push_back(prevs[i]);
	}

	// do next step
	size = nexts.size();
	if (size == 1)
		return nexts[0];
	else
		return last_card(nexts);
}

int main(void) {
	int
		i, // indexer
		N; // the number of cards

	vector<int> cards;

	cin >> N;
	cards.resize(N);
	for (i = 0; i < N; i++) {
		cards[i] = i + 1;
	}

	cout << last_card(cards);

	return 0;
}