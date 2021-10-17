#include <iostream>
#include <stack>
#include <vector>

using namespace std;

struct Range {
	int in_order_start;
	int in_order_end;
	int post_order_start;
	int post_order_end;
};

int main(void) {
	int n; // the number of numbers

	vector<int>
		in_order_index, // index 0 not used
		post_order;

	stack<Range> printing_stack;

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	// init
	cin >> n;
	in_order_index.resize(n + 1);
	post_order.resize(n);

	// get in-order
	for (int i = 0; i < n; i++) {
		int num;
		cin >> num;
		in_order_index[num] = i;
	}

	// get post-order
	for (int i = 0; i < n; i++) {
		cin >> post_order[i];
	}

	printing_stack.push({ 0, n - 1, 0, n - 1 });
	while (!printing_stack.empty()) {
		// pop one
		Range &range = printing_stack.top();
		int in_order_start = range.in_order_start;
		int in_order_end = range.in_order_end;
		int post_order_start = range.post_order_start;
		int post_order_end = range.post_order_end;
		printing_stack.pop();

		int root = post_order[post_order_end];
		int in_order_index_of_root = in_order_index[root];
		int n_left = in_order_index_of_root - in_order_start;
		int n_right = in_order_end - in_order_index_of_root;

		// print the local root
		cout << root << ' ';

		 // push all rights
		if (n_right > 0) {
			printing_stack.push({
				in_order_index_of_root + 1,
				in_order_end,
				post_order_start + n_left,
				post_order_end - 1,
			});
		}
		// push all lefts
		if (n_left > 0) {
			printing_stack.push({
				in_order_start,
				in_order_index_of_root - 1,
				post_order_start,
				post_order_start + n_left - 1,
			});
		}
	}

	return 0;
}
