#include <vector>

using namespace std;

inline int calculate_score(vector<int> target, int n) {
	int score = 0;
	int
	t1 = target[0],
	t2 = target[1],
	t3 = target[2],
	n1 = n / 100,
	n2 = (n % 100) / 10,
	n3 = n % 10;

	if (t1 == n1) score += 10;
	if (t1 == n2 || t1 == n3) score++;
	if (t2 == n2) score += 10;
	if (t2 == n1 || t2 == n3) score++;
	if (t3 == n3) score += 10;
	if (t3 == n1 || t3 == n2) score++;

	return score;
}

int solution(vector<vector<int>> baseball) {
	int i, j, k, n, n_baseball, n_candidate, score;
	vector<vector<int>> candidates;

	// init candidates
	for (i = 1; i < 10; i++) {
		for (j = 1; j < 10; j++) {
			if (j == i) continue;
			for (k = 1; k < 10; k++) {
				if (k == j || k == i) continue;
				candidates.push_back({i, j, k});
			}
		}
	}

	// filtering
	n_baseball = baseball.size();
	for (i = 0; i < n_baseball; i++) {
		n_candidate = candidates.size();
		for (j = 0; j < n_candidate; j++) {
			n = baseball[i][0];
			score = baseball[i][1] * 10 + baseball[i][2];
			if (score != calculate_score(candidates[j], n)) {
				candidates.erase(candidates.begin() + j);
				n_candidate--;
				j--;
			}
		}
	}

	return candidates.size();
}