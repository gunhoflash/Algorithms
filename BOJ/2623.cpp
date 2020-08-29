#include <iostream>
#include <vector>

using namespace std;

int main(void) {
	int
		i, j, // indexer
		size, // size of a vector
		N, // the number of singers
		M, // the number of PDs
		singer_prev, singer_next; // singers

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	vector<vector<int>> singers_next; // singers after itself
	vector<int> n_singers_before; // the numbers of singers before itself
	vector<int> answer;

	// index 0 never used

	// set the number of singers
	cin >> N;
	singers_next.resize(N + 1, vector<int>());
	n_singers_before.resize(N + 1, 0);

	// set all PDs
	cin >> M;
	while (M--) {
		cin >> i; // the number of singers that PD is responsible for
		
		if (i == 0) continue;

		cin >> singer_prev;
		while (--i) {
			cin >> singer_next;
			singers_next[singer_prev].push_back(singer_next);
			n_singers_before[singer_next]++;
			singer_prev = singer_next;
		}
	}

	// look for all the firsts
	for (i = 1; i <= N; i++) {
		if (n_singers_before[i] == 0) {
			answer.push_back(i);
		}
	}

	// look others
	i = 0;
	while (i < answer.size()) {
		// see the next one
		singer_prev = answer[i++];

		// look nexts
		size = singers_next[singer_prev].size();
		for (j = 0; j < size; j++) {
			singer_next = singers_next[singer_prev][j];
			n_singers_before[singer_next]--;
			if (n_singers_before[singer_next] == 0) {
				answer.push_back(singer_next);
			}
		}
	}

	if (i == N) {
		// all singers can sing!
		for (i = 0; i < N; i++) {
			cout << answer[i] << '\n';
		}
	} else {
		// impossible order of singers!
		cout << '0';
	}

	return 0;
}