#include <string>
#include <vector>
#include <queue>

#define INT_MAX	2147483647

using namespace std;

bool is_1_diff(string a, string b) {
	int i, len, diff;
	
	diff = 0;
	len = a.size();
	for (i = 0; i < len; i++) {
		if (a[i] != b[i]) diff++;
	}

	return diff == 1;
}

int solution(string begin, string target, vector<string> words) {
	vector<vector<int>> matrix;
	vector<int> min_step;
	queue<int> visits;
	int i, j, n, now, step;

	// push the begin string into the words
	words.push_back(begin);
	n = words.size();
	
	// init matrix and min_step
	for (i = 0; i < n; i++) {
		matrix.push_back(vector<int>(n, 0));
		min_step.push_back(INT_MAX);
	}
	for (i = 0; i < n - 1; i++) {
		for (j = i + 1; j < n; j++) {
			if (is_1_diff(words[i], words[j])) {
				matrix[i][j] = matrix[j][i] = 1;
			}
		}
	}

	// start from n - 1
	min_step[n - 1] = 0;
	visits.push(n - 1);

	while (!visits.empty()) {
		now = visits.front();
		visits.pop();
		step = min_step[now];

		for (i = 0; i < n; i++) {
			if (matrix[now][i] == 1 && min_step[i] > step + 1) {
				min_step[i] = step + 1;
				visits.push(i);
			}
		}
	}

	// find target
	for (i = 0; i < n; i++) {
		if (words[i] == target) {
			if (min_step[i] == INT_MAX) {
				return 0;
			} else {
				return min_step[i];
			}
		}
	}
	return 0;
}