#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main(void) {
	int
		i, j, k, // indexers
		person,
		N, // the number of people
		M, // the number of parties
		n_know_truth, // the number of people who know the truth
		n_people_in_party, // the number of people in a party
		answer;

	vector<bool> know_truth; // index 0 not used
	vector<vector<bool>> is_acquaintance; // index 0 not used
	vector<vector<int>> party_people;
	queue<int> visiting_queue;

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N >> M;
	cin >> n_know_truth;

	// init vectors
	know_truth.resize(N + 1, false);
	is_acquaintance.resize(N + 1, vector<bool>(N + 1, false));
	party_people.resize(M);

	// init {know_truth}
	for (i = 0; i < n_know_truth; i++) {
		cin >> person;
		know_truth[person] = true;
	}

	// config {party_people} and {is_acquaintance}
	for (i = 0; i < M; i++) {
		// get the number of people in a party
		cin >> n_people_in_party;
		party_people[i].resize(n_people_in_party);

		for (j = 0; j < n_people_in_party; j++) {
			// get a person
			cin >> person;
			party_people[i][j] = person;

			// make relationships
			for (k = 0; k < j; k++) {
				is_acquaintance[party_people[i][k]][person] = true;
				is_acquaintance[person][party_people[i][k]] = true;
			}
		}
	}

	// BFS to spread truth
	for (i = 1; i < N + 1; i++) {
		if (!know_truth[i]) continue;

		// spread the truth from this person
		visiting_queue.push(i);
		while (!visiting_queue.empty()) {
			// pop one
			person = visiting_queue.front();
			visiting_queue.pop();

			// look for acquaintances
			for (j = 1; j < N + 1; j++) {
				if (is_acquaintance[person][j]) {
					if (!know_truth[j]) {
						// spread the truth to person-{j}
						know_truth[j] = true;
						visiting_queue.push(j);
					}
				}
			}
		}
	}

	// calculate the answer
	answer = 0;
	for (i = 0; i < M; i++) {
		if (party_people[i].size() == 0) {
			answer++;
		} else if (!know_truth[party_people[i][0]]) {
			answer++;
		}
	}

	cout << answer;

	return 0;
}