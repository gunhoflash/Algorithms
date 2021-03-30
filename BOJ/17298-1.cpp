#define INF 1000001

#include <iostream>
#include <stack>
#include <vector>

using namespace std;

struct Element {
	int value;
	int nge;
	int nge_index;
};

int main(void) {
	int N; // length of sequence
	vector<Element> elements;

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	// get length of sequence
	cin >> N;

	// init elements
	elements.resize(N + 1);

	// get all values
	for (int i = 0; i < N; i++) {
		cin >> elements[i].value;
	}
	elements[N].value = INF;

	for (int i = N - 1; i >= 0; i--) {
		// find NGE
		int value = elements[i].value;
		int nge_index = i + 1;

		while (elements[nge_index].value <= value) {
			nge_index = elements[nge_index].nge_index;
		}

		elements[i].nge = elements[nge_index].value;
		elements[i].nge_index = nge_index;
	}

	// print the answer
	for (int i = 0; i < N; i++) {
		int nge = elements[i].nge;
		cout << (nge == INF ? -1 : nge) << ' ';
	}

	return 0;
}