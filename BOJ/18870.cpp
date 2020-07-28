#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

bool cmp_second(pair<int, int> a, pair<int, int> b) {
	return a.second < b.second;
}

int main(void) {
	int i, N, n, order;
	vector<pair<int, int>> numbers; // [[number, index_original], ...]

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	// set N
	cin >> N;
	numbers.resize(N, pair<int, int>());

	// get numbers(coordinates)
	for (i = 0; i < N; i++) {
		cin >> n;
		numbers[i].first = n;
		numbers[i].second = i;
	}

	// sort by number in ascending order
	sort(numbers.begin(), numbers.end());

	// save order(compress coordinates)
	order = 0;
	n = numbers[0].first;
	for (i = 0; i < N; i++) {
		// if this one is bigger than the previous one
		if (numbers[i].first > n) {
			// save it
			n = numbers[i].first;
			order++;
		}
		// if not, follow the previous's order
		numbers[i].first = order;
	}

	// sort in original order
	sort(numbers.begin(), numbers.end(), cmp_second);

	// print out
	for (i = 0; i < N; i++) {
		cout << numbers[i].first << ' ';
	}

	return 0;
}