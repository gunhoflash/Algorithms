#include <iostream>
#include <map>

using namespace std;

int main(void) {
	int
		i,                            // indexer
		stalagmite, stalactite, N, H, // input
		n_stalagmites, n_stalactites, // the number of obstacles
		min_n_obstacles, n_routes,    // answers
		temp;

	map<int, int> stalagmites, stalactites;

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	// get data
	cin >> N >> H;
	for (i = 0; i < N; i += 2) {
		cin >> stalagmite >> stalactite;
		if (!stalagmites[stalagmite]) stalagmites[stalagmite] = 1;
		else stalagmites[stalagmite]++;
		if (!stalactites[stalactite]) stalactites[stalactite] = 1;
		else stalactites[stalactite]++;
	}

	// check from bottom to top
	n_routes = 0;
	min_n_obstacles = N;
	n_stalactites = 0;
	n_stalagmites = N / 2;
	for (i = 1; i <= H; i++) {
		if (stalagmites[i - 1]) n_stalagmites -= stalagmites[i - 1];
		if (stalactites[H - i + 1]) n_stalactites += stalactites[H - i + 1];
		temp = n_stalagmites + n_stalactites;

		if (temp < min_n_obstacles) {
			// new minimum
			min_n_obstacles = temp;
			n_routes = 1;
		} else if (temp == min_n_obstacles) {
			// same minimum
			n_routes++;
		}
	}

	cout << min_n_obstacles << ' ' << n_routes;
	return 0;
}