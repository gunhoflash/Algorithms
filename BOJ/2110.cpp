#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

using namespace std;

int binary_search_max(int min, int max, function<bool(int)> f) {
	while (min <= max) {
		int mid = (min + max) >> 1;
		if (f(mid)) {
			min = mid + 1;
		} else {
			max = mid - 1;
		}
	}
	return max;
}

int main(void) {
	int N, C;

	vector<int> houses;
	
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	// init array
	cin >> N >> C;
	houses.resize(N);
	for (int i = 0; i < N; i++) {
		cin >> houses[i];
	}

	// sort houses in ascending order
	sort(houses.begin(), houses.end());

	// get the maximum of minimum distance between routers
	int answer = binary_search_max(1, (houses.back() - houses.front()) / (C - 1), [&](int distance) {
		int n_router = 1;
		int prev = houses[0];
		for (int house : houses) {
			if (house - prev >= distance) {
				prev = house;
				n_router++;
			}
		}
		return n_router >= C;
	});

	// print the answer
	cout << answer;

	return 0;
}
