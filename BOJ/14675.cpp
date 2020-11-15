#include <iostream>
#include <vector>

using namespace std;

int main(void) {
	int
		N, // the number of nodes
		a, b, // info of an edge
		q, // the number of queries
		t, k; // info of a query

	vector<int> n_connected;

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	// get the number of nodes
	cin >> N;

	// init {n_connected}
	n_connected.resize(N + 1, 0);

	// get all edges
	while (--N) {
		cin >> a >> b;
		n_connected[a]++;
		n_connected[b]++;
	}

	// get all queries
	cin >> q;
	while (q--) {
		cin >> t >> k;
		cout << ((t == 2 || n_connected[k] > 1) ? "yes\n" : "no\n");
	}

	return 0;
}