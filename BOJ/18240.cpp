#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Node {
	int id;
	int left_bound;
	int sub_tree_size;
	Node *parent;
	Node *left_child;
	Node *right_child;
};

int main(void) {
	int
		i, j, // indexers
		size, // size of a vector
		N, // the number of nodes
		depth;

	Node
		*child,
		*parent;

	vector<Node> nodes; // index 0 is for root
	vector<int> depth_nodes_indexers;
	vector<vector<Node *>> depth_nodes;

	queue<Node *> visiting_queue;

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	// get the number of nodes
	cin >> N;
	nodes.resize(N);

	// add the root node
	nodes[0].parent = NULL;
	nodes[0].left_child = NULL;
	nodes[0].right_child = NULL;

	// init {depth_nodes_indexers} and {depth_nodes}
	depth_nodes_indexers.resize(N, 0);
	depth_nodes.resize(N);
	depth_nodes[0].push_back(&(nodes[0]));

	// get all depths
	for (i = 1; i < N; i++) {
		cin >> depth;
		j = depth_nodes_indexers[depth - 1];

		// handle exception: invalid depth
		if (j >= depth_nodes[depth - 1].size()) {
			cout << "-1";
			return 0;
		}

		child = &(nodes[i]);
		parent = depth_nodes[depth - 1][j];

		// init the child node
		child->parent = parent;
		child->left_child = NULL;
		child->right_child = NULL;

		// add child to parent
		if (parent->left_child == NULL) {
			// add left child
			parent->left_child = child;
		} else {
			// add right child
			parent->right_child = child;
			depth_nodes_indexers[depth - 1]++;
		}

		// register the new node to depth tree
		depth_nodes[depth].push_back(child);
	}

	// set size of sub-tree
	for (i = N - 1; i >= 0; i--) {
		size = depth_nodes[i].size();
		for (j = 0; j < size; j++) {
			parent = depth_nodes[i][j];
			if (parent->right_child != NULL) {
				// full children node
				parent->sub_tree_size =
					parent->left_child->sub_tree_size +
					parent->right_child->sub_tree_size;
			} else if (parent->left_child != NULL) {
				// right child node
				parent->sub_tree_size =
					parent->left_child->sub_tree_size;
			}
			parent->sub_tree_size++;
		}
	}

	// set ID for all nodes from the root to leaf
	nodes[0].left_bound = 1;
	visiting_queue.push(&(nodes[0]));
	while (!visiting_queue.empty()) {
		// pop one
		parent = visiting_queue.front();
		visiting_queue.pop();

		// set ID
		parent->id = parent->left_bound;

		// check left child
		child = parent->left_child;
		if (child != NULL) {
			parent->id += child->sub_tree_size;
			child->left_bound = parent->left_bound;
			visiting_queue.push(child);
		}

		// check right child
		child = parent->right_child;
		if (child != NULL) {
			child->left_bound = parent->id + 1;
			visiting_queue.push(child);
		}
	}

	// print the answer
	for (i = 0; i < N; i++) {
		cout << nodes[i].id << ' ';
	}

	return 0;
}