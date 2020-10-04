#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main(void) {
	int
		i, // indexer
		N; // the number of points

	vector<pair<int, int>> points;

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	// get all points
	cin >> N;
	points.resize(N);
	for (i = 0; i < N; i++) {
		cin >> points[i].second;
		cin >> points[i].first;
	}

	// sort
	sort(points.begin(), points.end());

	// print out
	for (i = 0; i < N; i++) {
		cout << points[i].second << ' ' << points[i].first << '\n';
	}

	return 0;
}