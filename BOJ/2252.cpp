#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main(void) {
	int
		i, // indexer
		size, // size of a vector
		N, // the number of students
		M, // the number of comparisons
		A, B; // students

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	vector<vector<int>> students_next; // students after itself
	vector<int> n_students_before; // the numbers of students before itself
	queue<int> visiting_queue;

	// index 0 never used

	// set the number of students
	cin >> N;
	students_next.resize(N + 1, vector<int>());
	n_students_before.resize(N + 1, 0);

	// set all comparisons
	cin >> M;
	while (M--) {
		cin >> A >> B;
		students_next[A].push_back(B);
		n_students_before[B]++;
	}

	// look for all the short
	for (i = 1; i <= N; i++) {
		if (n_students_before[i] == 0) {
			visiting_queue.push(i);
		}
	}

	// look others
	while (!visiting_queue.empty()) {
		// pop one
		A = visiting_queue.front();
		visiting_queue.pop();

		cout << A << ' ';

		// look nexts
		size = students_next[A].size();
		for (i = 0; i < size; i++) {
			B = students_next[A][i];
			n_students_before[B]--;
			if (n_students_before[B] == 0) {
				visiting_queue.push(B);
			}
		}
	}

	return 0;
}