#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

bool cmp(pair<int, int> &p, pair<int, int> &q) {
	if (p.first != q.first) {
		return p.first > q.first;
	} else {
		return p.second < q.second;
	}
}

int main(void) {
	vector<int> n_hackables;
	vector<vector<int>> trusted;

	vector<int> visiting;
	vector<bool> is_visited;

	vector<pair<int, int>> max_hackers;

	int
		i, j, k, // indexer
		now, neighbor, // for DFS
		N, // the number of computers
		M, // the number of relationships
		A, B, // computers ( A trust B )
		n_hackable,
		max_n_hackables;

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N >> M;

	// init computers
	n_hackables.resize(N + 1, 0);
	trusted.resize(N + 1, vector<int>());
	is_visited.resize(N + 1, false);
	max_hackers.resize(N + 1);

	// make relationships
	while (M--) {
		cin >> A >> B;
		trusted[B].push_back(A);
	}

	for (i = 1; i <= N; i++) {

		// init
		for (j = 1; j <= N; j++) {
			is_visited[j] = false;
		}

		// start from {i}
		is_visited[i] = true;
		visiting.push_back(i);
		n_hackable = 1;

		// DFS
		while (visiting.size()) {

			// visit {j}
			now = visiting.back();
			visiting.pop_back();

			// look neighbors
			for (int neighbor: trusted[now]) {

				// already visited
				if (is_visited[neighbor]) continue;
				is_visited[neighbor] = true;
				n_hackable++;
				visiting.push_back(neighbor);
			}
		}
		max_hackers[i].first = n_hackable;
		max_hackers[i].second = i;
	}

	// print out max hackers
	max_hackers[0].first = 0;
	sort(max_hackers.begin(), max_hackers.end(), cmp);

	max_n_hackables = max_hackers[0].first;
	for (i = 0; i < N; i++) {
		if (max_hackers[i].first == max_n_hackables) {
			cout << max_hackers[i].second << ' ';
		} else {
			break;
		}
	}

	return 0;
}