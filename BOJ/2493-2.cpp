#define MAX_HEIGTH 100000000

#include <iostream>
#include <stack>

using namespace std;

struct Tower {
	int height;
	int index;
};

int main(void) {
	int N;
	stack<Tower> towers;

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	// get the number of towers
	cin >> N;

	// init towers
	towers.push({ MAX_HEIGTH + 1, 0 });

	for (int i = 1; i <= N; i++) {
		int height;

		// get height of tower
		cin >> height;

		// pop all lower towers before
		while (height > towers.top().height) towers.pop();

		// print the target
		cout << towers.top().index << ' ';

		// save the tower
		towers.push({ height, i });
	}

	return 0;
}