#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Point {
	int x;
	int y;
	bool is_visited;
	vector<int> nears;
};

inline bool is_near(Point a, Point b) {
	int dx = a.x - b.x;
	int dy = a.y - b.y;
	if (dx < 0) dx *= -1;
	if (dy < 0) dy *= -1;
	return dx + dy <= 1000;
}

int main(void) {
	int i, j, t, n, size;
	vector<Point> cvs_list;
	queue<int> visiting_queue;
	Point now, goal;

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	// for every test
	cin >> t;
	while (t--) {
		// init
		cvs_list.clear();
		while (!visiting_queue.empty()) visiting_queue.pop();

		cin >> n;
		cvs_list.resize(n + 1, Point());

		// convert to vector of Point
		for (i = 0; i < n + 1; i++) {
			cvs_list[i].is_visited = false;
			cin >> cvs_list[i].x;
			cin >> cvs_list[i].y;
			for (j = 0; j < i; j++) {
				if (is_near(cvs_list[i], cvs_list[j])) {
					cvs_list[i].nears.push_back(j);
					cvs_list[j].nears.push_back(i);
				}
			}
		}
		cin >> goal.x;
		cin >> goal.y;
		goal.is_visited = false;

		// bfs starting from cvs_list[0]
		cvs_list[0].is_visited = true;
		visiting_queue.push(0);
		while (!visiting_queue.empty()) {

			// pop front
			now = cvs_list[visiting_queue.front()];
			visiting_queue.pop();

			// check whether is is near the goal
			if (is_near(now, goal)) {
				goal.is_visited = true;
				break;
			}

			// check near points
			size = now.nears.size();
			for (i = 0; i < size; i++) {
				if (cvs_list[now.nears[i]].is_visited == false) {
					cvs_list[now.nears[i]].is_visited = true;
					visiting_queue.push(now.nears[i]);
				}
			}
		}

		if (goal.is_visited) {
			cout << "happy\n";
		} else {
			cout << "sad\n";
		}
	}

	return 0;
}