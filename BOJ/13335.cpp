#include <iostream>
#include <queue>

using namespace std;

int main(void) {
	int
		n, // the number of trucks
		w, // length of bridge
		L, // maximum load
		total_load,
		time;

	queue<int>
		waiting_queue,
		load;

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> w >> L;

	// init bridge
	total_load = 0;
	while (w--) load.push(0);

	// init queue
	while (n--) {
		int weight;
		cin >> weight;
		waiting_queue.push(weight);
	}

	// do simulation
	time = 0;
	while (!waiting_queue.empty() || total_load > 0) {
		time++;

		// go forward
		total_load -= load.front();
		load.pop();

		// new truck or not
		if (!waiting_queue.empty()) {
			int next_load = waiting_queue.front();
			if (total_load + next_load <= L) {
				total_load += next_load;
				waiting_queue.pop();
				load.push(next_load);
			} else {
				load.push(0);
			}
		} else {
			load.push(0);
		}
	}

	// print the answer
	cout << time;

	return 0;
}