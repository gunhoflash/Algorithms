#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main(void) {
	vector<int> max_heap;
	int N, x;

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N;
	while (N--) {
		cin >> x;
		if (x == 0) {
			if (max_heap.empty()) {
				// heap is empty
				cout << "0\n";
			} else {
				// pop the max
				pop_heap(max_heap.begin(), max_heap.end());
				cout << max_heap.back() << '\n';
				max_heap.pop_back();
			}
		} else {
			// push the number to heap
			max_heap.push_back(x);
			push_heap(max_heap.begin(), max_heap.end());
		}
	}

	return 0;
}