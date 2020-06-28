#include <vector>
#include <queue>

using namespace std;

int solution(int n, vector<vector<int>> computers) {
	int i, n_connected, answer;
	vector<bool> is_connected(n, false);
	queue<int> searching_queue;
	vector<int> computer;

	// init variables
	answer = 0;
	n_connected = 0;

	while (n_connected < n) {

		// select a new starting point
		for (i = 0; i < n; i++) {
			if (!is_connected[i]) {
				n_connected++;
				is_connected[i] = true;
				searching_queue.push(i);
				break;
			}
		}

		// BFS
		while (!searching_queue.empty()) {
			computer = computers[searching_queue.front()];
			for (i = 0; i < n; i++) {
				if (computer[i] == 1 && !is_connected[i]) {
					n_connected++;
					is_connected[i] = true;
					searching_queue.push(i);
				}
			}
			searching_queue.pop();
		}

		answer++;
	}

	return answer;
}