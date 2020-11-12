#include <algorithm>
#include <iostream>
#include <vector>

#define max(a, b) (a > b ? a : b)

using namespace std;

struct Node {
	int node_id;
	int depth;
	int max_sub_length;
	vector<int> children_id;
	vector<int> children_weight;
};

bool compare_nodes(Node &a, Node &b) {
	return a.depth > b.depth;
}

int main(void) {
	int
		i, j, // indexer
		n_children, // the number of children
		n, // the number of nodes
		parent, child, weight, // info of an edge
		sub_length, first_max_sub_length, second_max_sub_length,
		diameter, max_diameter;

	Node *node;
	vector<Node> nodes; // index 0 not used
	vector<Node *> node_pointers; // index 0 not used

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	// get the number of nodes
	cin >> n;

	// init all nodes
	nodes.resize(n + 1);
	node_pointers.resize(n + 1);
	for (i = 0; i < n + 1; i++) {
		nodes[i].node_id = i;
		nodes[i].depth = 0;
		nodes[i].max_sub_length = 0;
	}

	// get all edges
	for (i = 0; i < n - 1; i++) {
		cin >> parent >> child >> weight;

		// set depth
		nodes[child].depth = nodes[parent].depth + 1;

		// add child
		nodes[parent].children_id.push_back(child);
		nodes[parent].children_weight.push_back(weight);
	}

	// sort by depth
	sort(nodes.begin() + 1, nodes.end(), compare_nodes);

	// set pointers
	for (i = 0; i < n + 1; i++) {
		node_pointers[nodes[i].node_id] = &(nodes[i]);
	}

	// check maximum diameter
	// from bottom to top
	max_diameter = 0;
	for (i = 1; i < n + 1; i++) {
		node = &(nodes[i]);

		// check all sub-lengths
		n_children = node->children_id.size();
		first_max_sub_length = 0;
		second_max_sub_length = 0;
		for (j = 0; j < n_children; j++) {
			sub_length = node_pointers[node->children_id[j]]->max_sub_length + node->children_weight[j];
			if (sub_length > first_max_sub_length) {
				second_max_sub_length = first_max_sub_length;
				first_max_sub_length = sub_length;
			} else if (sub_length > second_max_sub_length) {
				second_max_sub_length = sub_length;
			}
		}

		// update maximum diameter
		node->max_sub_length = first_max_sub_length;
		diameter = first_max_sub_length + second_max_sub_length;
		max_diameter = max(max_diameter, diameter);
	}

	// print the answer
	cout << max_diameter;
	return 0;
}