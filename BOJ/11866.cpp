#include <iostream>
#include <queue>

using namespace std;

int main(void) {
	int N, K;
	queue<int> q;

	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> K;
	for (int i = 1; i <= N; i++) {
		q.push(i);
	}

	K--;
	cout << '<';
	while (true) {
		int k = K;
		while (k--) {
			q.push(q.front());
			q.pop();
		}

		cout << q.front();
		q.pop();
		if (q.empty()) break;
		cout << ", ";
	}
	cout << '>';

	return 0;
}