#include <functional>
#include <iostream>
#include <vector>

using namespace std;

int binary_search_max(long long min, long long max, function<bool(int)> f) {
	while (min <= max) {
		long long mid = (min + max) >> 1;
		if (f((int)mid)) {
			min = mid + 1;
		} else {
			max = mid - 1;
		}
	}
	return max;
}

int main(void) {
	int K, N;

	vector<int> cables;
	
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	// init array
	cin >> K >> N;
	cables.resize(K);
	for (int i = 0; i < K; i++) {
		cin >> cables[i];
	}

	int answer = binary_search_max(1, 2147483647, [&](int length) {
		int sum = 0;
		for (int cable : cables) {
			sum += cable / length;
		}
		return sum >= N;
	});

	// print the answer
	cout << answer;

	return 0;
}
