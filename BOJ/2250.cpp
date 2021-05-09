#include <algorithm>
#include <climits>
#include <iostream>
#include <queue>
#include <stack>
#include <vector>

#define NONE -1

using namespace std;

struct Node {
	int parent = 0;
	int left_child;
	int right_child;
	int row = 0; // negative: cannot visit, 0: visitable
};

struct Row {
	int left;
	int right;
};

int main(void) {
	int
		N,
		root,
		column = 1,
		n_rows = 0,
		max_width = 0,
		row_with_max_width;

	queue<int> visiting_queue;
	stack<int> visiting_stack;
	vector<Node> nodes; // index 0 never used
	vector<Row> rows(1); // index 0 never used

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	// init all nodes
	cin >> N;
	nodes.resize(N + 1);
	for (int i = 0; i < N; i++) {
		int n, left_child, right_child;
		cin >> n >> left_child >> right_child;

		nodes[n].left_child = left_child;
		nodes[n].right_child = right_child;

		if (left_child == NONE && right_child == NONE) {
			// leaf node
			visiting_queue.push(n);
			continue;
		}

		if (left_child != NONE) {
			// left child exist
			nodes[n].row--;
			nodes[left_child].parent = n;
		}
		if (right_child != NONE) {
			// right child exist
			nodes[n].row--;
			nodes[right_child].parent = n;
		}
	}

	// visit all nodes from bottom
	while (!visiting_queue.empty()) {
		// pop one
		int
			n = visiting_queue.front(),
			parent = nodes[n].parent;
		visiting_queue.pop();

		// check parent
		if (parent) {
			if (++nodes[parent].row == 0) {
				visiting_queue.push(parent);
			}
		} else {
			root = n;
		}
	}

	// visit all nodes from root
	visiting_stack.push(root);
	while (!visiting_stack.empty()) {
		// pop one
		int
			n = visiting_stack.top(),
			parent = nodes[n].parent,
			row = parent ? nodes[parent].row + 1 : 1,
			left_child = nodes[n].left_child,
			right_child = nodes[n].right_child;

		// calculate row
		nodes[n].row = row;

		// visit left children first
		if (left_child != NONE) {
			nodes[n].left_child = NONE;
			visiting_stack.push(left_child);
			continue;
		}
		visiting_stack.pop();

		// visit right children after
		if (right_child != NONE) {
			visiting_stack.push(right_child);
		}

		// visit node

		while (row > n_rows) {
			rows.push_back({ NONE, NONE });
			n_rows++;
		}

		if (rows[row].left == NONE) {
			rows[row].left = rows[row].right = column;
		} else {
			rows[row].left = min(rows[row].left, column);
			rows[row].right = max(rows[row].right, column);
		}
		column++;
	}

	// print the answer
	for (int row = 1; row <= n_rows; row++) {
		int width = rows[row].right - rows[row].left + 1;
		if (width > max_width) {
			max_width = width;
			row_with_max_width = row;
		}
	}
	cout << row_with_max_width << ' ' << max_width;

	return 0;
}
