#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main(void) {
	int N, x;
	vector<int> min_heap;

	cin.tie(NULL);
	cout.tie(NULL);

	// get the number of commands
	cin >> N;

	while (N--) {
		cin >> x;
		if (x == 0) {
			// pop
			if (min_heap.empty()) {
				// print 0 when the heap is empty
				cout << "0\n";
			} else {
				pop_heap(min_heap.begin(), min_heap.end(), greater<int>());
				cout << min_heap.back() << '\n';
				min_heap.pop_back();
			}
		} else {
			// push
			min_heap.push_back(x);
			push_heap(min_heap.begin(), min_heap.end(), greater<int>());
		}
	}

	return 0;
}