#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct BlockTower {
	int height;
	int left_max;
	int right_max;
};

int main(void) {
	int H, W, answer;
	vector<BlockTower> towers;

	cin >> H >> W;

	// get all heights
	towers.resize(W);
	for (int i = 0; i < W; i++) {
		cin >> towers[i].height;
	}

	// set left max
	towers[0].left_max = 0;
	for (int i = 1; i < W; i++) {
		towers[i].left_max = max(towers[i - 1].left_max, towers[i - 1].height);
	}

	// set right max
	towers[W - 1].right_max = 0;
	for (int i = W - 2; i >= 0; i--) {
		towers[i].right_max = max(towers[i + 1].right_max, towers[i + 1].height);
	}

	// collect water
	answer = 0;
	for (int i = 0; i <  W; i++) {
		answer += max(min(towers[i].left_max, towers[i].right_max) - towers[i].height, 0);
	}

	// print the answer
	cout << answer;

	return 0;
}