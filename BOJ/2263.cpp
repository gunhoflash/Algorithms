// preorder:  root - left  - right
// inorder:   left - root  - right
// postorder: left - right - root

#include <iostream>
#include <stack>
#include <vector>

using namespace std;

int main(void) {
	int
		i, j, // indexers
		number, // number
		n, // the number of numbers
		index_start,
		index_end;

	vector<int>
		inorder_index, // index 0 not used
		postorder;

	stack<pair<int, int>>
		printing_stack; // { start index, end index }

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	// init
	cin >> n;
	inorder_index.resize(n + 1);
	postorder.resize(n);

	// get inorder
	for (i = 0; i < n; i++) {
		cin >> number;
		inorder_index[number] = i;
	}

	// get postorder
	for (i = 0; i < n; i++) {
		cin >> postorder[i];
	}

	printing_stack.push({ 0, n - 1 });
	while (!printing_stack.empty()) {
		// pop one
		index_start = printing_stack.top().first;
		index_end = printing_stack.top().second;
		printing_stack.pop();

		// print the local root
		cout << postorder[index_end] << ' ';

		// divide left and right

		// get inorder index of root
		i = inorder_index[postorder[index_end]];

		// find all the right
		for (j = index_end - 1; j >= index_start; j--) {
			if (inorder_index[postorder[j]] <= i) break;
		}

		// print all the right
		if (j + 1 <= index_end - 1) {
			printing_stack.push({ j + 1, index_end - 1 });
		}

		// print all the left
		if (j >= index_start) {
			printing_stack.push({ index_start, j });
		}
	}

	return 0;
}