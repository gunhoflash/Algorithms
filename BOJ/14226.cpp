#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct State {
	int value;
	int clipboard;
	int cost;
};

inline void visit_next(int value, int clipboard, int cost, queue<State> &visiting_queue, vector<vector<bool>> &is_visited) {
	if (!is_visited[value][clipboard]) {
		is_visited[value][clipboard] = true;
		visiting_queue.push({ value, clipboard, cost });
	}
}

int main(void) {
	int S;
	vector<vector<bool>> is_visited;
	queue<State> visiting_queue;

	cin >> S;
	is_visited.resize(S * 2, vector<bool>(S, false));
	is_visited[1][0] = true;
	visiting_queue.push({ 1, 0, 0 });

	while (true) {
		// pop one
		int
			next_value,
			value = visiting_queue.front().value,
			clipboard = visiting_queue.front().clipboard,
			cost = visiting_queue.front().cost;
		visiting_queue.pop();

		// end of searching
		if (value == S) {
			cout << cost;
			break;
		}

		// method 1
		if (clipboard != value && value < S) {
			visit_next(value, value, cost + 1, visiting_queue, is_visited);
		}

		// method 2
		next_value = value + clipboard;
		if (next_value < S * 2) {
			visit_next(next_value, clipboard, cost + 1, visiting_queue, is_visited);
		}

		// method 3
		next_value = value - 1;
		if (next_value >= 0) {
			visit_next(next_value, clipboard, cost + 1, visiting_queue, is_visited);
		}
	}

	return 0;
}
