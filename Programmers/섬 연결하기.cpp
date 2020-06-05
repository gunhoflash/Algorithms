#include <vector>
#include <algorithm>

using namespace std;

bool cmp(vector<int> a, vector<int> b) {
	return a[2] < b[2];
}

int solution(int n, vector<vector<int>> costs) {
	int i, len, n_connected, answer;
	vector<bool> connected;

	// init connected
	connected.resize(n, false);

	// sort costs
	sort(costs.begin(), costs.end(), cmp);

	// start from island 0
	n_connected = 1;
	connected[0] = true;

	// search other islands
	len = costs.size();
	answer = 0;
	while (n_connected != n) {
		for (i = 0; i < len; i++) {
			if (connected[costs[i][0]] != connected[costs[i][1]]) {
				n_connected++;
				connected[costs[i][0]] = connected[costs[i][1]] = true;
				answer += costs[i][2];
				break;
			}
		}
	}

	return answer;
}