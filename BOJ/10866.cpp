#include <iostream>
#include <queue>

using namespace std;

inline void print(int n) {
	cout << n << '\n';
}

int main(void) {
	int N;
	deque<int> dq;

	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N;
	while (N--) {
		string command;
		cin >> command;

		switch (command[0]) {
			case 'p':
			switch (command[1]) {
				case 'u':
				int x;
				cin >> x;
				if (command[5] == 'f') {
					dq.push_front(x);
				} else {
					dq.push_back(x);
				}
				break;

				case 'o':
				if (dq.empty()) {
					print(-1);
					break;
				}
				if (command[4] == 'f') {
					print(dq.front());
					dq.pop_front();
				} else {
					print(dq.back());
					dq.pop_back();
				}
				break;
			}
			break;

			case 's':
			print(dq.size());
			break;

			case 'e':
			print(dq.empty() ? 1 : 0);
			break;

			case 'f':
			print(dq.empty() ? -1 : dq.front());
			break;

			case 'b':
			print(dq.empty() ? -1 : dq.back());
			break;
		}
	}

	return 0;
}