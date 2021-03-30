#include <iostream>
#include <stack>
#include <vector>

using namespace std;

struct Element {
	int value;
	int index;
};

int main(void) {
	int N; // length of sequence
	vector<int> nge;
	stack<Element> elements;

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	// get length of sequence
	cin >> N;

	// init NGE
	nge.resize(N);

	// get all values
	for (int i = 0; i < N; i++) {
		int value;
		cin >> value;

		// pop all lower elements before
		while (!elements.empty() && value > elements.top().value) {
			nge[elements.top().index] = value;
			elements.pop();
		}

		// save the element
		elements.push({ value, i });
	}

	// pop all remained elements
	while (!elements.empty()) {
		nge[elements.top().index] = -1;
		elements.pop();
	}

	// print the answer
	for (int i = 0; i < N; i++) {
		cout << nge[i] << ' ';
	}

	return 0;
}