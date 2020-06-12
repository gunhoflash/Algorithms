#include <algorithm>
#include <vector>

using namespace std;

int solution(vector<int> people, int limit) {

	vector<pair<int, int>> weights;
	vector<pair<int, int>>::iterator it;

	int i, answer, temp_weight, temp_n_weight, remained_weights, n_people = people.size();

	// sort people
	sort(people.begin(), people.end(), greater<int>());
	temp_weight = people[0];
	temp_n_weight = 1;

	// init weights from people
	for (i = 1; i < n_people; i++) {
		if (people[i] == temp_weight) {
			// same weight
			temp_n_weight++;
		} else {
			// new weight
			weights.push_back(make_pair(temp_weight, temp_n_weight));
			temp_weight = people[i];
			temp_n_weight = 1;
		}
	}
	weights.push_back(make_pair(temp_weight, temp_n_weight));

	// let's rescue everybody!
	answer = 0;
	while (!weights.empty()) {

		remained_weights = limit;
		it = weights.begin();
		n_people = 0;

		while (it != weights.end()) {
			if (it->first <= remained_weights) {
				// get ride on
				remained_weights -= it->first;
				it->second--;
				n_people++;

				if (it->second == 0)
					it = weights.erase(it);


				// nobody can't ride more
				if (remained_weights < temp_weight || n_people == 2)
					break;

			} else {
				it++;
			}
		}

		// boat go go go
		if (n_people > 0) answer++;
	}

	return answer;
}