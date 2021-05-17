#include <iostream>
#include <queue>
#include <set>
#include <vector>

using namespace std;

struct Node {
	Node *parent;
	set<Node *> children;
};

int main(void) {
	int
		N, // the number of nodes
		target, // the node to delete
		answer = 0; // the number of leaf nodes

	vector<Node> nodes;

	queue<Node *> visiting_queue;

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	// init all nodes
	cin >> N;
	nodes.resize(N);
	for (int i = 0; i < N; i++) {
		int parent;
		cin >> parent;
		if (parent != -1) {
			nodes[i].parent = &nodes[parent];
			nodes[parent].children.insert(&nodes[i]);
		} else {
			visiting_queue.push(&nodes[i]);
		}
	}

	// delete node from the tree
	cin >> target;

	if (nodes[target].parent != NULL) {
		nodes[target].parent->children.erase(&nodes[target]);
		// start from the root node
		while (!visiting_queue.empty()) {
			Node *now = visiting_queue.front();
			visiting_queue.pop();

			if (now->children.size() == 0) {
				answer++;
			} else {
				for (Node *child : now->children) {
					visiting_queue.push(child);
				}
			}
		}
	}

	// print the answer
	cout << answer;

	return 0;
}
