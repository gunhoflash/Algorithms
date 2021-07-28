#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

#define MAX_COST 1000000

using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int
		n, // the number of cities
		m; // the number of buses

	int min_cost[101][101];
	int prev_city[101][101] = { 0 };

	cin >> n >> m;

	// init min_cost
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			min_cost[i][j] = MAX_COST;
		}
		min_cost[i][i] = 0;
	}

	// get all buses
	for (int i = 0; i < m; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		if (c < min_cost[a][b]) {
			// new minimum cost from a to b
			min_cost[a][b] = c;
			prev_city[a][b] = a;
		}
	}

	// use floyd warshall algorithm
	for (int k = 1; k <= n; k++) {
		for (int a = 1; a <= n; a++) {
			for (int b = 1; b <= n; b++) {
				if (min_cost[a][b] > min_cost[a][k] + min_cost[k][b]) {
					min_cost[a][b] = min_cost[a][k] + min_cost[k][b];
					prev_city[a][b] = k;
				}
			}
		}
	}

	// print all costs between cities
	for (int a = 1; a <= n; a++) {
		for (int b = 1; b <= n; b++) {
			cout << (min_cost[a][b] == MAX_COST ? 0 : min_cost[a][b]) << ' ';
		}
		cout << '\n';
	}

	// print all routes between cities
	for (int a = 1; a <= n; a++) {
		for (int b = 1; b <= n; b++) {
			vector<int> route;

			if (prev_city[a][b] != 0) {
				// calculate the route from a to b
				stack<pair<int, int>> s;
				s.push(make_pair(a, b));
				while (!s.empty()) {
					int a = s.top().first;
					int b = s.top().second;
					int prev = prev_city[a][b];
					s.pop();

					if (prev == a) {
						// no more route
						route.push_back(a);
					} else {
						// complecated route
						s.push(make_pair(prev, b));
						s.push(make_pair(a, prev));
					}
				}
				route.push_back(b);
			}

			// print length of the route
			cout << route.size();

			// print the route
			for (int i = 0; i < route.size(); i++) {
				cout << ' ' << route[i];
			}
			cout << '\n';
		}
	}

	return 0;
}
