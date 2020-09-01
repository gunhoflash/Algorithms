#include <iostream>
#include <queue>

using namespace std;

int main(void) {
	int
		i, j, k, // indexer
		N, // the number of elements
		M, // the number of pops
		pop, // the number to pop
		size, // size of a vector
		answer;

	vector<int> q; // queue

	// get data
	cin >> N >> M;

	// init {q}
	q.resize(N);
	for (i = 0; i < N; i++) {
		q[i] = i + 1;
	}

	// pop M-elements
	answer = 0;
	size = N;
	i = 0;
	while (M--) {
		cin >> pop;

		if (q[i] != pop) {
			for (j = 1; j < size; j++) {
				answer++;

				k = (i + j) % size;
				if (q[k] == pop) {
					i = k;
					break;
				}

				k = (i - j + size) % size;
				if (q[k] == pop) {
					i = k;
					break;
				}
			}
		}

		// pop one
		q.erase(q.begin() + i);
		size--;
		if (i >= size) i -= size;
	}

	cout << answer;

	return 0;
}