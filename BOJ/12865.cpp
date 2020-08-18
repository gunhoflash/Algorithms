#include <iostream>
#include <map>

using namespace std;

int main(void) {
	int
		i,    // indexer
		N,    // the number of items: 1 ~     100
		K,    // maximum weight:      1 ~ 100,000
		W, w, // weight of each item: 1 ~ 100,000
		V, v; // value of each item:  0 ~   1,000

	map<int, int, greater<int>> weight_value;

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	// init
	weight_value[0] = 0;

	// get data
	cin >> N >> K;
	while (N--) {
		cin >> W >> V;

		// cannot handle this item
		if (W > K) continue;

		for (auto kv : weight_value) {

			w = kv.first + W;
			v = kv.second + V;

			// cannot handle this item
			if (w > K) continue;

			if (weight_value.find(w) == weight_value.end()) {
				// new weight
				weight_value[w] = v;
			} else {
				// compare with exist one
				if (v > weight_value[w]) {
					weight_value[w] = v;
				}
			}
		}
	}

	// find and print the maximum value
	v = 0;
	for (auto kv : weight_value) {
		v = (kv.second > v) ? kv.second : v;
	}
	cout << v;

	return 0;
}