#include <iostream>
#include <vector>

using namespace std;

struct Node {
	int left;
	int right;
};

int main(void) {
	int
		i, // indexer
		N, // the number of nodes
		U, V, // left, right node
		node_now; // index of now visiting node

	long long
		K; // the number of beads

	Node node; // now visiting node
	vector<Node> nodes;

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	// get all nodes
	cin >> N;
	nodes.resize(N + 1);
	for (i = 1; i <= N; i++) {
		cin >> nodes[i].left >> nodes[i].right;
	}

	// get the number of beads
	cin >> K;

	// start from node 1
	node_now = 1;
	while (K) {
		node = nodes[node_now];

		if (node.left == -1 && node.right == -1) {
			// no child
			break;
		}

		if (node.left == -1 || node.right == -1) {
			// only one child
			node_now = node.left + node.right + 1;
		} else {
			// 2 children
			if (K & 1) {
				// odd number
				node_now = node.left;
			} else {
				// even number
				node_now = node.right;
			}
			K = (K + 1) / 2;
		}
	}

	// print the answer
	cout << node_now;
	return 0;
}