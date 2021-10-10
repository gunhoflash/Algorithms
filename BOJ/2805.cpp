#include <algorithm>
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
	return min - 1;
}

int main(void) {
	int N, M;

	vector<int> trees;
	
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	// init array
	cin >> N >> M;
	trees.resize(N);
	for (int i = 0; i < N; i++) {
		cin >> trees[i];
	}

	// sort all trees
	sort(trees.begin(), trees.end());

	int answer = binary_search_max(1, trees.back(), [&](int height) {
		long long sum = 0;
		// cut trees
		for (int tree : trees) {
			sum += tree > height ? tree - height : 0;
		}
		return sum >= M;
	});

	// print the answer
	cout << answer;

	return 0;
}
