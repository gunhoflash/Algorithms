#include <iostream>
#include <vector>

using namespace std;

void make_pattern_index(vector<int> &pattern, vector<int> &pi) {
	int
		i, // indexer
		matched, // number of letters matched
		len; // length of a pattern

	// init {pi}
	len = pattern.size();
	pi.resize(len, 0);

	matched = 0;
	for (i = 1; i < len; i++) {
		while (matched > 0 && pattern[i] != pattern[matched]) {
			matched = pi[matched - 1];
		}
		if (pattern[i] == pattern[matched]) {
			matched++;
			pi[i] = matched;
		}
	}
}

bool has_pattern(vector<int> &program, vector<int> &pattern) {
	int
		i, // indexer
		matched, // number of letters matched
		len_program, len_pattern; // length of a vector

	vector<int> pi;

	len_program = program.size();
	len_pattern = pattern.size();

	// init {pi}
	make_pattern_index(pattern, pi);

		// start to find the pattern
	matched = 0;
	for (i = 0; i < len_program; i++) {
		while (matched > 0 && program[i] != pattern[matched]) {
			matched = pi[matched - 1];
		}

		if (program[i] == pattern[matched]) {
			matched++;
			if (matched == len_pattern) {
				pi.clear();
				return true;
			}
		}
	}

	pi.clear();
	return false;
}

bool has_virus() {
	int
		i, j, // indexers
		p, // piece of a program
		N, // the number of programs
		K, // minimum length of virus
		M; // length of a program

	vector<vector<int>> programs;
	vector<vector<int>> programs_reversed;
	vector<int> virus;

	// get data
	cin >> N >> K;
	programs.resize(N, vector<int>());
	programs_reversed.resize(N, vector<int>());
	for (i = 0; i < N; i++) {
		cin >> M;

		// early stop
		if (M < K) {
			return false;
		}

		// get program data
		programs[i].resize(M);
		programs_reversed[i].resize(M);
		for (j = 0; j < M; j++) {
			cin >> p;
			programs[i][j] = programs_reversed[i][M - j - 1] = p;
		}
	}

	// init candidate
	virus.resize(K);
	for (i = 0; i < K - 1; i++) {
		virus[i] = programs[0][i];
	}

	M = programs[0].size();
	do {
		virus[K - 1] = programs[0][i];

		// check for all programs
		for (j = 1; j < N; j++) {
			if (!has_pattern(programs[j], virus)) {
				if (!has_pattern(programs_reversed[j], virus)) {
					break;
				}
			}
		}
		if (j == N) {
			// virus found
			return true;
		}

		// look for next candidate
		for (j = 0; j < K - 1; j++) {
			virus[j] = virus[j + 1];
		}
	} while (++i < M);

	// virus not found
	return false;
}

int main(void) {

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cout << (has_virus() ? "YES" : "NO");

	return 0;
}