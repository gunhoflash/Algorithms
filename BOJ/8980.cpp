#include <algorithm>
#include <iostream>
#include <vector>

#define min(a, b) (a < b ? a : b)

using namespace std;

struct Request {
	int from;
	int to;
	int n_box;
};

bool compare_request(const Request &a, const Request &b) {
	if (a.to != b.to) {
		return a.to < b.to;
	} else {
		return a.from > b.from;
	}
}

int main(void) {
	int
		i, // indexer
		N, // the number of villages
		C, // capacity of truck
		M, // the number of request
		delivered_boxes; // the number of delivered boxes

	vector<int>
		carriable;

	vector<Request>
		requests;

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	// get the number of villages and capacity of the truck
	cin >> N >> C;
	carriable.resize(N, C);

	// get all requests
	cin >> M;
	requests.resize(M);
	for (i = 0; i < M; i++) {
		cin >> requests[i].from >> requests[i].to >> requests[i].n_box;
	}

	// sort all requests
	sort(requests.begin(), requests.end(), compare_request);

	// check all requests in order
	delivered_boxes = 0;
	for (i = 0; i < M; i++) {
		int from = requests[i].from;
		int to = requests[i].to;
		int max_deliverable = min(requests[i].n_box, C);

		// check the maximum number of deliverable boxes
		for (int j = from; j < to; j++) {
			max_deliverable = min(max_deliverable, carriable[j]);
		}

		// deliver some boxes
		if (max_deliverable > 0) {
			for (int j = from; j < to; j++) {
				carriable[j] -= max_deliverable;
			}
			delivered_boxes += max_deliverable;
		}
	}

	cout << delivered_boxes;

	return 0;
}