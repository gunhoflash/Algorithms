#define N 101
#define MAX_DISTANCE 100000000

#include <iostream>
#include <vector>

using namespace std;

int main(void) {
	int
		n, // the number of area
		m, // search scope
		r; // the number of roads

	// index 0 is not used
	vector<vector<int>> distance;
	vector<int> n_item;

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> m >> r;

	// init all distances
	distance.resize(n + 1, vector<int>(n + 1, MAX_DISTANCE));

	// set the number of items for each area
	n_item.resize(n + 1);
	for (int i = 1; i <= n; i++) {
		cin >> n_item[i];
	}

	// set all distances between areas
	for (int i = 0; i < r; i++) {
		int a, b, l;
		cin >> a >> b >> l;
		distance[a][b] = distance[b][a] = l;
	}

	// use Floyd-Warshall Algorithm
	for (int k = 1; k <= n; k++) {
		distance[k][k] = 0;
		for (int i = 1;	i <= n; i++) {
			for (int j = 1;	j <= n; j++) {
				if (distance[i][k] + distance[k][j] < distance[i][j]) {
					distance[i][j] = distance[i][k] + distance[k][j];
				}
			}
		}
	}

	int max_sum_item = 0;
	for (int i = 1;	i <= n; i++) {
		// calculate sum of item when start from area-i
		int sum_item = 0;
		for (int j = 1;	j <= n; j++) {
			if (distance[i][j] <= m) {
				sum_item += n_item[j];
			}
		}
		// update maximum
		if (sum_item > max_sum_item) {
			max_sum_item = sum_item;
		}
	}

	// print the answer
	cout << max_sum_item;

	return 0;
}