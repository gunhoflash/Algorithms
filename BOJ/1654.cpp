#include <iostream>
#include <vector>

using namespace std;

int main(void) {
	int
		answer,
		sum,
		temp,
		i, // indexer
		K, // the number of LAN cable have
		N; // the number of LAN cable wanted

	long long
		answer_upperbound,
		answer_lowerbound;

	vector<int> cables;
	
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	// get data
	cin >> K >> N;
	cables.resize(K);
	for (i = 0; i < K; i++) {
		cin >> cables[i];
	}

	// find the answer
	answer_upperbound = 2147483647;
	answer_lowerbound = 1;
	while (true) {

		sum = 0;
		answer = (answer_upperbound + answer_lowerbound) / 2;

		for (i = 0; i < K; i++) {
			sum += cables[i] / answer;
		}

		if (sum < N) {
			answer_upperbound = answer - 1;
		} else {
			if (answer_upperbound == answer_lowerbound) {
				break;
			} else if (answer_upperbound == answer_lowerbound + 1) {
				sum = 0;
				for (i = 0; i < K; i++) {
					sum += cables[i] / answer_upperbound;
				}
				if (sum >= N) answer = answer_upperbound;
				else answer = answer_lowerbound;
				break;
			} else {
				answer_lowerbound = answer;
			}
		}
	}

	// print the answer
	cout << answer;

	return 0;
}