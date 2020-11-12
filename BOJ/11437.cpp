#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Node {
	int id;
	int depth;
	Node *parent;
	vector<Node *> adjacents;
};

int main(void) {
	int
		i, j, // indexers
		N, // the number of nodes
		M, // the number of node pairs
		depth, depth1, depth2, // depth of nodes
		node_id_1, node_id_2, // nodes
		n_adjacents; // the number of adjacents

	Node *node1, *node2;
	vector<Node> nodes; // index 0 not used
	queue<Node *> visiting_queue;

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	// get the number of nodes
	cin >> N;

	// init all nodes
	nodes.resize(N + 1);
	for (i = 1; i <= N; i++) {
		nodes[i].id = i;
		nodes[i].depth = -1;
	}
	nodes[1].depth = 0;

	// get all edges
	for (i = 0; i < N - 1; i++) {
		cin >> node_id_1 >> node_id_2;
		nodes[node_id_1].adjacents.push_back(&nodes[node_id_2]);
		nodes[node_id_2].adjacents.push_back(&nodes[node_id_1]);
	}

	// set depth of all nodes
	visiting_queue.push(&(nodes[1]));
	while (!visiting_queue.empty()) {
		// pop one
		node1 = visiting_queue.front();
		visiting_queue.pop();
		depth = node1->depth + 1;

		// look for adjacent
		n_adjacents = node1->adjacents.size();
		for (i = 0; i < n_adjacents; i++) {
			node2 = node1->adjacents[i];
			if (node2->depth == -1) {
				node2->depth = depth;
				node2->parent = node1;
				visiting_queue.push(node2);
			}
		}
	}

	// get the number of pairs
	cin >> M;
	while (M--) {
		// get pairs
		cin >> node_id_1 >> node_id_2;
		node1 = &(nodes[node_id_1]);
		node2 = &(nodes[node_id_2]);

		// get depth
		depth1 = node1->depth;
		depth2 = node2->depth;

		// go up until the same depth
		while (depth1 > depth2) {
			node1 = node1->parent;
			depth1--;
		}
		while (depth2 > depth1) {
			node2 = node2->parent;
			depth2--;
		}

		// go up until same parent node
		while (node1 != node2) {
			node1 = node1->parent;
			node2 = node2->parent;
		}

		// print the same parent node
		cout << node1->id << '\n';
	}

	return 0;
}