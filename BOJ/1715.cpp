#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main(void) {
	vector<int> min_heap;
	int N, card, answer, top1, top2;

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	// get data and make min-heap
	cin >> N;
	min_heap.resize(N);
	while (N--) cin >> min_heap[N];
	make_heap(min_heap.begin(), min_heap.end(), greater<int>());

	// calculate the answer
	answer = 0;
	while (min_heap.size() > 1) {
		top1 = min_heap.front();
		pop_heap(min_heap.begin(), min_heap.end(), greater<int>());
		min_heap.pop_back();
		top2 = min_heap.front();
		pop_heap(min_heap.begin(), min_heap.end(), greater<int>());
		min_heap.back() += top1;
		push_heap(min_heap.begin(), min_heap.end(), greater<int>());
		answer += top1 + top2;
	}

	// print answer
	cout << answer;

	return 0;
}