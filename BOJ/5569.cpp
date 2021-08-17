#include <iostream>

#define MAX_SIZE_MAP 101
#define MOD 100000

using namespace std;

struct Crossroad {
	int from_west = 0;
	int from_south = 0;
};

int main () {
	Crossroad map[MAX_SIZE_MAP][MAX_SIZE_MAP];
	int w, h;

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> w >> h;

	// init crossroads on border
	for (int i = 1; i <= w; i++) {
		map[i][1].from_west = 1;
	}
	for (int j = 1; j <= h; j++) {
		map[1][j].from_south = 1;
	}

	// init crossroads at inner
	for (int i = 2; i <= w; i++) {
		for (int j = 2; j <= h; j++) {
			map[i][j].from_west = (map[i - 1][j].from_west + map[i - 1][j - 1].from_south) % MOD;
			map[i][j].from_south = (map[i][j - 1].from_south + map[i - 1][j - 1].from_west) % MOD;
		}
	}

	// print the answer
	cout << (map[w][h].from_south + map[w][h].from_west) % MOD;
	return 0;
}
