#define MAX 1000000

#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

inline void set_multiples(int n, int step, queue<int> &q, vector<int> &steps) {
	int limit_index = steps.size();
	for (int i = n; i < limit_index; i *= 2) {
		if (steps[i] != MAX) break; 
		steps[i] = step;
		q.push(i);
	}
}

int main(void) {
	int N, K, limit_index;

	vector<int> steps;
	queue<int> visiting_queue;

	// get position
	cin >> N >> K;

	// quick pass
	if (N >= K) {
		cout << N - K;
		return 0;
	}

	// init step
	steps.resize(K + K / 2 + 1, MAX);

	set_multiples(N, 0, visiting_queue, steps);
	while (!visiting_queue.empty()) {
		// pop one
		int n = visiting_queue.front();
		visiting_queue.pop();
		int step = steps[n];

		// end of searching
		if (n == K) {
			cout << step;
			break;
		}

		// go next
		if (n > 1)
			set_multiples(n - 1, step + 1, visiting_queue, steps);
		set_multiples(n + 1, step + 1, visiting_queue, steps);
	}

	return 0;
}
