#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main(void) {
	int
		i, // indexer
		size, // size of a vector
		N, // the number of problems
		M, // the number of comparisons
		A, B; // problems

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	vector<vector<int>> problems_next; // problems after itself
	vector<int> n_problems_before; // the numbers of problems before itself
	priority_queue<int, vector<int>, greater<int>> visiting_queue;

	// index 0 never used

	// set the number of problems
	cin >> N;
	problems_next.resize(N + 1, vector<int>());
	n_problems_before.resize(N + 1, 0);

	// set all comparisons
	cin >> M;
	while (M--) {
		cin >> A >> B;
		problems_next[A].push_back(B);
		n_problems_before[B]++;
	}

	// look for all the firsts
	for (i = 1; i <= N; i++) {
		if (n_problems_before[i] == 0) {
			visiting_queue.push(i);
		}
	}

	// look others
	while (!visiting_queue.empty()) {
		// pop one
		A = visiting_queue.top();
		visiting_queue.pop();

		cout << A << ' ';

		// look nexts
		size = problems_next[A].size();
		for (i = 0; i < size; i++) {
			B = problems_next[A][i];
			n_problems_before[B]--;
			if (n_problems_before[B] == 0) {
				visiting_queue.push(B);
			}
		}
	}

	return 0;
}