#include <iostream>
#include <set>

using namespace std;

int main(void) {
	int
		i, // indexer
		G, // the number of gates
		P, // the number of airplanes
		gi, // gate option: the maximum dockable gate number for a plane
		n_dockable;

	set<int>
		available_gates;

	set<int>::iterator
		it_available_gate;

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	// get the number of gates and airplanes
	cin >> G >> P;

	// init {available_gates}
	for (i = 1; i <= G; i++) {
		available_gates.insert(-i);
	}

	// get the sequence of gate option
	n_dockable = 0;
	for (i = 0; i < P; i++) {
		// get option
		cin >> gi;
		it_available_gate = available_gates.lower_bound(-gi);
		if (it_available_gate != available_gates.end()) {
			// assign the gate
			available_gates.erase(it_available_gate);
			n_dockable++;
		} else {
			// close the airport
			break;
		}
	}

	// print the answer
	cout << n_dockable;

	return 0;
}