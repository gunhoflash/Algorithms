#include <algorithm>
#include <functional>
#include <iostream>

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
	int N, K;

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N >> K;

	int answer = binary_search_max(1, K, [&](int value) {
		int integral = 0;
		for (int i = min(value, N); i; i--) {
			integral += min(N, value / i);
		}
		return integral < K;
	}) + 1;

	// print the answer
	cout << answer;

	return 0;
}
