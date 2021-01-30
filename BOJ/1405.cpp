#include <iostream>
#include <stack>

using namespace std;

typedef int t_path; // 0b...332211
#define EAST  0b00
#define WEST  0b01
#define SOUTH 0b10
#define NORTH 0b11

struct PathState {
	t_path path;
	int length;
	double probability;
};

bool is_simple_path(t_path path, int path_length) {
	int dx = 0, dy = 0;
	while (path_length--) {
		switch (path & 0b11) {
			case EAST:  dx++; break;
			case WEST:  dx--; break;
			case SOUTH: dy++; break;
			case NORTH: dy--; break;
		}
		path >>= 2;

		// back to the start: not simple path
		if (dx == 0 && dy == 0) return false;
	}

	// it is simple path
	return true;
}

int main(void) {
	int
		path_length; // length of path

	double
		probability_simple = 0, // probability of taking simple path 
		probability_E,      // probability of moving east
		probability_W,      // probability of moving west
		probability_S,      // probability of moving south
		probability_N;      // probability of moving north

	PathState
		now, next;

	stack<PathState>
		pathstates;

	// get length of path and probabilities
	cin
		>> path_length
		>> probability_E
		>> probability_W
		>> probability_S
		>> probability_N;

	// resize probabilities (0 ~ 1)
	probability_E /= 100;
	probability_W /= 100;
	probability_S /= 100;
	probability_N /= 100;

	// start searching
	pathstates.push({
		0, // path
		0, // length
		1 // probability
	});
	while (!pathstates.empty()) {
		// pop one
		now = pathstates.top();
		pathstates.pop();

		// check length
		if (now.length == path_length) {
			// simple full-length path
			probability_simple += now.probability;
		} else {
			// set next direction
			now.length++;
			now.path <<= 2;

			// E
			if (probability_E) {
				next = now;
				next.path |= EAST;
				if (is_simple_path(next.path, next.length)) {
					next.probability *= probability_E;
					pathstates.push(next);
				}
			}
			// W
			if (probability_W) {
				next = now;
				next.path |= WEST;
				if (is_simple_path(next.path, next.length)) {
					next.probability *= probability_W;
					pathstates.push(next);
				}
			}
			// S
			if (probability_S) {
				next = now;
				next.path |= SOUTH;
				if (is_simple_path(next.path, next.length)) {
					next.probability *= probability_S;
					pathstates.push(next);
				}
			}
			// N
			if (probability_N) {
				next = now;
				next.path |= NORTH;
				if (is_simple_path(next.path, next.length)) {
					next.probability *= probability_N;
					pathstates.push(next);
				}
			}
		}
	}

	// print the answer
	cout.precision(12);
	cout << probability_simple;

	return 0;
}