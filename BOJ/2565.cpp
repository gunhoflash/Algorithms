#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct Line {
	int from;
	int to;
	int ascending_length;
};

bool compare_line(const Line &a, const Line &b) {
	return a.from < b.from;
}

int main(void) {
	int
		i, j, // indexer
		n_line, // the number of lines
		max_ascending_length; // the number of deleted lines

	vector<Line>
		lines;

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	// set lines
	cin >> n_line;
	lines.resize(n_line);
	for (i = 0; i < n_line; i++) {
		cin >> lines[i].from >> lines[i].to;
	}

	// sort by from
	sort(lines.begin(), lines.end(), compare_line);

	// set ascending length
	max_ascending_length = 0;
	for (i = 0; i < n_line; i++) {
		int to = lines[i].to;
		int ascending_length = 1;
		for (j = 0; j < i; j++) {
			if (lines[j].to < to) {
				ascending_length = max(ascending_length, lines[j].ascending_length + 1);
			}
		}
		lines[i].ascending_length = ascending_length;
		max_ascending_length = max(max_ascending_length, ascending_length);
	}

	// print the answer
	cout << n_line - max_ascending_length;

	return 0;
}
