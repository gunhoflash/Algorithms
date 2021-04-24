#include <iostream>
#include <vector>
#include <stack>

using namespace std;

int main(void) {
	int N, length;

	vector<int>
		sequence,
		before_index,
		last, last_index;

	stack<int>
		answer;

	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N;
	sequence.resize(N);
	before_index.resize(N);

	for (int i = 0; i < N; i++) {
		int n;
		cin >> n;

		sequence[i] = n;
		length = last.size();

		vector<int>::iterator it = lower_bound(last.begin(), last.end(), n);

		if (it == last.end()) {
			before_index[i] = length ? last_index[length - 1] : -1;
			last.push_back(n);
			last_index.push_back(i);
		} else {
			int index = it - last.begin();
			(*it) = n;
			before_index[i] = index ? last_index[index - 1] : -1;
			last_index[index] = i;
		}
	}

	length = last.size();
	cout << length << '\n';

	int i = last_index[length - 1];
	while (length--) {
		answer.push(sequence[i]);
		i = before_index[i];
	}

	while (!answer.empty()) {
		cout << answer.top() << ' ';
		answer.pop();
	}

	return 0;
}
