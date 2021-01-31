#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main(void) {
	int
		N, // the number of students
		M, // the number of relationships
		X, // target student
		A, B, // info of a relationship
		n_up_X = 0,
		n_down_X = 0;

	vector<vector<int>>
		up,
		down;

	vector<bool>
		is_visited;

	queue<int>
		visiting_queue;

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	// get data
	cin >> N >> M >> X;

	// init vectors
	up.resize(N + 1);
	down.resize(N + 1);
	is_visited.resize(N + 1, false);

	// set relationships
	while (M--) {
		cin >> A >> B;
		up[B].push_back(A);
		down[A].push_back(B);
	}

	// find all up
	visiting_queue.push(X);
	while (!visiting_queue.empty()) {
		// pop one
		B = visiting_queue.front();
		visiting_queue.pop();

		// check up
		for (auto A : up[B]) {
			if (!is_visited[A]) {
				is_visited[A] = true;
				n_up_X++;
				visiting_queue.push(A);
			}
		}
	}

	// find all down
	is_visited.assign(N, false);
	visiting_queue.push(X);
	while (!visiting_queue.empty()) {
		// pop one
		A = visiting_queue.front();
		visiting_queue.pop();

		// check up
		for (auto B : down[A]) {
			if (!is_visited[B]) {
				is_visited[B] = true;
				n_down_X++;
				visiting_queue.push(B);
			}
		}
	}

	// print the answer
	cout << 1 + n_up_X << ' ' << N - n_down_X;

	return 0;
}