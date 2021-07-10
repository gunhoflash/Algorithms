#include <iostream>
#include <vector>

using namespace std;

int find(int v, vector<int> &group) {
	if (group[v] == v) return v;
	return group[v] = find(group[v], group);
}

void connect(int a, int b, vector<int> &group) {
	int group_a = find(a, group);
	int group_b = find(b, group);

	if (group_a != group_b) {
		group[group_b] = group_a;
	}
}

int main(void) {
	int N;
	vector<int> group;

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N;

	// init groups
	group.resize(N + 1);
	for (int i = 1; i <= N; i++) {
		group[i] = i;
	}

	for (int i = 0; i < N - 2; i++) {
		int a, b;
		cin >> a >> b;

		connect(a, b, group);
	}

	int group_before = find(1, group);
	for (int i = 2; i <= N; i++) {
		if (find(i, group) != group_before) {
			cout << group_before << ' ' << i;
			break;
		}
	}

	return 0;
}
