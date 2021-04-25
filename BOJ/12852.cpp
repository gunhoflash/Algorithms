#define MAX 10000000
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main(void) {
	int N;
	vector<int> n_step, before;
	queue<int> visiting_queue;

	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N;
	n_step.resize(N + 1, MAX);
	before.resize(N + 1);

	n_step[1] = 0;
	before[1] = -1;
	visiting_queue.push(1);
	while (true) {
		int n = visiting_queue.front();
		int step = n_step[n];

		if (n == N) break;
		visiting_queue.pop();

		if (n * 3 <= N && n_step[n * 3] == MAX) {
			n_step[n * 3] = step + 1;
			before[n * 3] = n;
			visiting_queue.push(n * 3);
		}
		if (n * 2 <= N && n_step[n * 2] == MAX) {
			n_step[n * 2] = step + 1;
			before[n * 2] = n;
			visiting_queue.push(n * 2);
		}
		if (n < N && n_step[n + 1] == MAX) {
			n_step[n + 1] = step + 1;
			before[n + 1] = n;
			visiting_queue.push(n + 1);
		}
	}

	cout << n_step[N] << '\n';
	while (N != -1) {
		cout << N << ' ';
		N = before[N];
	}

	return 0;
}