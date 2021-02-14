#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main(void) {
	int
		N, // the number of scales
		max_weight_available;

	vector<int>
		scales;

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	// get all scales
	cin >> N;
	scales.resize(N);
	for (int i = 0; i < N; i++) {
		cin >> scales[i];
	}

	// sort scales
	sort(scales.begin(), scales.end());

	max_weight_available = 0;
	for (auto scale : scales) {
		if (scale <= max_weight_available + 1) {
			max_weight_available += scale;
		} else {
			// answer found
			break;
		}
	}

	// print the answer
	cout << max_weight_available + 1;

	return 0;
}