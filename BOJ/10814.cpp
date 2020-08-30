#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(void) {
	int
		i, // indexer
		N, // the number of clients
		age;
		
	string name;

	vector<pair<pair<int, int>, string>> clients; // [ [ [ age, order ], name ], ... ]

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	// get data
	cin >> N;
	clients.resize(N);
	for (i = 0; i < N; i++) {
		cin >> clients[i].first.first;
		cin >> clients[i].second;
		clients[i].first.second = i;
	}

	// sort clients
	sort(clients.begin(), clients.end());

	// print in order
	for (i = 0; i < N; i++) {
		cout << clients[i].first.first << ' ' << clients[i].second << '\n';
	}

	return 0;
}