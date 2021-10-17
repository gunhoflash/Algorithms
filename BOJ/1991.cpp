#include <iostream>
#include <vector>

#define NONE_ALPHABET '.'
#define NONE_NUMBER -1

using namespace std;

struct Node {
	int left, right;
};

inline int alphabet_to_number(char c) {
  return c == NONE_ALPHABET ? NONE_NUMBER : c - 'A';
}

inline char number_to_alphabet(int n) {
  return n == NONE_NUMBER ? NONE_ALPHABET : 'A' + n;
}

void print_pre_order(vector<Node> &nodes, int root) {
	if (root == NONE_NUMBER) return;
	cout << number_to_alphabet(root);
	print_pre_order(nodes, nodes[root].left);
	print_pre_order(nodes, nodes[root].right);
}

void print_in_order(vector<Node> &nodes, int root) {
	if (root == NONE_NUMBER) return;
	print_in_order(nodes, nodes[root].left);
	cout << number_to_alphabet(root);
	print_in_order(nodes, nodes[root].right);
}

void print_post_order(vector<Node> &nodes, int root) {
	if (root == NONE_NUMBER) return;
	print_post_order(nodes, nodes[root].left);
	print_post_order(nodes, nodes[root].right);
	cout << number_to_alphabet(root);
}

int main() {
	int N;
	vector<Node> nodes;

	// get the number of nodes
	cin >> N;
	nodes.resize(N);

	// construct the tree
	while (N--) {
		char node, left, right;
		cin >> node >> left >> right;
		nodes[alphabet_to_number(node)].left = alphabet_to_number(left);
		nodes[alphabet_to_number(node)].right = alphabet_to_number(right);
	}

	print_pre_order(nodes, 0);
	cout << '\n';
	print_in_order(nodes, 0);
	cout << '\n';
	print_post_order(nodes, 0);
	cout << '\n';

	return 0;
}
