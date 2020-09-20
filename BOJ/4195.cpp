#include <iostream>
#include <map>

using namespace std;

map<string, pair<string, int>> parent_and_size;

string get_parent(string name) {
	if (parent_and_size[name].first == name) {
		// name is root
		return name;
	} else {
		// update parent and return
		return parent_and_size[name].first = get_parent(parent_and_size[name].first);
	}
}

// merge and return the size
int merge(string a, string b) {
	string root_a = get_parent(a);
	string root_b = get_parent(b);

	if (root_a != root_b) {
		// merge root_b into root_a
		parent_and_size[root_a].second += parent_and_size[root_b].second;
		parent_and_size[root_b].first = root_a;
	}

	return parent_and_size[root_a].second;
}

int main(void) {
	int
		i, // indexer
		n_test_case, // the number of test case
		F; // the number of relations

	string friend_a, friend_b; // relation

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	// set the number of test case
	cin >> n_test_case;
	while (n_test_case--) {
		// init {parent_and_size}
		parent_and_size.clear();

		// set the number of relations
		cin >> F;
		while (F--) {
			cin >> friend_a >> friend_b;

			// new friend
			if (parent_and_size.find(friend_a) == parent_and_size.end()) {
				parent_and_size[friend_a] = { friend_a, 1 };
			}
			// new friend
			if (parent_and_size.find(friend_b) == parent_and_size.end()) {
				parent_and_size[friend_b] = { friend_b, 1 };
			}

			// merge friends and print the size of network
			cout << merge(friend_a, friend_b) << '\n';
		}
	}

	return 0;
}