#include <iostream>
#include <map>
#include <string>

using namespace std;

int main(void) {
	int n_tree = 0;
	map<string, int> tree_map;

	// get all names of tree
	while (!cin.eof()) {
		string tree_name;
		getline(cin, tree_name);
		if (tree_name.length() == 0) break;

		map<string, int>::iterator tree = tree_map.find(tree_name);
		if (tree == tree_map.end()) {
			tree_map.insert({ tree_name, 1 });
		} else {
			tree->second++;
		}

		n_tree++;
	}

	// print the answer
	cout << fixed;
	cout.precision(4);
	for (auto tree : tree_map) {
		cout << tree.first << ' ' << 100.0 * tree.second / n_tree << '\n';
	}

	return 0;
}