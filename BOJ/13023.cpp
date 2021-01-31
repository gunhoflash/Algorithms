#include <iostream>
#include <set>
#include <stack>
#include <vector>

using namespace std;

struct State {
	int now;
	set<int> visited;
};

int main(void) {
	int
		N, // the number of people
		M, // the number of relationships
		a, b, // friends
		depth_5_exist = 0;

	State
		now_state, next_state;

	vector<vector<int>>
		adjacent;

	stack<State>
		visiting_stack;

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	// init people
	cin >> N;
	adjacent.resize(N, vector<int>());

	// set relationships
	cin >> M;
	while (M--) {
		cin >> a >> b;
		adjacent[a].push_back(b);
		adjacent[b].push_back(a);
	}

	for (int i = 0; i < N; i++) {
		visiting_stack.push({ i, { i } });
		while (!visiting_stack.empty()) {
			// pop one
			now_state = visiting_stack.top();
			visiting_stack.pop();

			// end: depth 5 found
			if (now_state.visited.size() == 5) {
				depth_5_exist = 1;
				break;
			}

			// check adjacent
			for (auto next : adjacent[now_state.now]) {
				if (now_state.visited.find(next) == now_state.visited.end()) {
					// visit next
					next_state = now_state;
					next_state.now = next;
					next_state.visited.insert(next);
					visiting_stack.push(next_state);
				}
			}
		}

		if (depth_5_exist) break;
	}

	// print the answer
	cout << depth_5_exist;

	return 0;
}
