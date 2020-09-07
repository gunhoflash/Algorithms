#include <iostream>
#include <vector>

using namespace std;

int main(void) {
	int
		i, // indexer
		N, // the number of people
		K; // removing gap

	vector<int> people;

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	// get data
	cin >> N >> K;

	// set people
	people.resize(N);
	for (i = 0; i < N; i++)
		people[i] = i + 1;

	// optimize K
	K--;

	cout << '<';

	// repeat until no one exist
	i = 0;
	while (N) {
		i = (i + K) % N;

		// remove the person
		cout << people[i];
		if (--N) {
			cout << ", ";
		}
		people.erase(people.begin() + i);
	}

	cout << '>';

	return 0;
}