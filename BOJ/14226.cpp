#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct State {
	int value;
	int clipboard;
	int cost;
};

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
		int next_value;
		int value = visiting_queue.front().value;
		int clipboard = visiting_queue.front().clipboard;
		int cost = visiting_queue.front().cost;
		visiting_queue.pop();

		// end of searching
		if (value == S) {
			cout << cost;
			break;
		}

		// method 1
		if (clipboard != value && value < S) {
			if (!is_visited[value][value]) {
				is_visited[value][value] = true;
				visiting_queue.push({
					value,
					value,
					cost + 1
				});
			}
		}

		// method 2
		next_value = value + clipboard;
		if (next_value < S * 2) {
			if (!is_visited[next_value][clipboard]) {
				is_visited[next_value][clipboard] = true;
				visiting_queue.push({
					next_value,
					clipboard,
					cost + 1
				});
			}
		}

		// method 3
		next_value = value - 1;
		if (next_value >= 0) {
			if (!is_visited[next_value][clipboard]) {
				is_visited[next_value][clipboard] = true;
				visiting_queue.push({
					next_value,
					clipboard,
					cost + 1
				});
			}
		}
	}

	return 0;
}
