// 여러 줄 입력 관련 문제로 코드가 지저분함. 수정 필요함.
#include <iostream>
#include <vector>
#include <stack>

using namespace std;

struct Range {
	int start;
	int end;
};

// find index of the maximum value which is smaller than the target
int binary_search_max_index(vector<int>& numbers, int left, int right, int target) {
	while (left <= right) {
		int mid = (left + right) / 2;

		if (numbers[mid] > target) {
			right = mid - 1;
		} else {
			left = mid + 1;
		}
	}
	return right;
}

int main() {
	vector<int> pre_order;
	stack<Range> searching_stack;

	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	// get pre_order
	while (!cin.eof()) {
		int num;
		cin >> num;
		pre_order.push_back(num);
	}

	int n_node = pre_order.size();
	if (pre_order[n_node - 1] == pre_order[n_node - 2]) {
		pre_order.pop_back();
		n_node--;
	}

	searching_stack.emplace(Range{ 0, n_node - 1 });
	while (!searching_stack.empty()) {
		int start = searching_stack.top().start;
		int end = searching_stack.top().end;
		searching_stack.pop();

		// the first element of range is root
		int root = pre_order[start];

		// print the node
		if (start == end) {
			cout << root << '\n';
			continue;
		}

		int index_left_max = binary_search_max_index(pre_order, start + 1, end, root);

		// search root
		searching_stack.emplace(Range{ start, start });

		// if right sub-tree exist, search right sub-tree
		if (index_left_max < end) {
			searching_stack.emplace(Range{ index_left_max + 1, end });
		}

		// if left sub-tree exist, search left sub-tree
		if (start < index_left_max) {
			searching_stack.emplace(Range{ start + 1, index_left_max });
		}
	}

	return 0;
}
