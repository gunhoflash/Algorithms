#define MAX_HEIGTH 100000000

#include <iostream>
#include <vector>

using namespace std;

int main(void) {
	int N;
	vector<int> targets, heights;

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	// get the number of towers
	cin >> N;

	// init targets
	targets.resize(N + 1);

	// init heights
	heights.resize(N + 1);
	heights[0] = MAX_HEIGTH + 1;

	for (int i = 1; i <= N; i++) {
		int height, prev_tower_index;

		// get height of tower
		cin >> height;

		// find target
		prev_tower_index = i - 1;
		while (heights[prev_tower_index] < height) {
			prev_tower_index = targets[prev_tower_index];
		}

		// save
		targets[i] = prev_tower_index;
		heights[i] = height;

		// print target
		cout << prev_tower_index << ' ';
	}

	return 0;
}