#include <iostream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

int main(void) {
	int
		i, // indexer
		last_pushed,
		pop, // a number to pop
		n;

	vector<string> answer;
	stack<int> st;

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	last_pushed = 0;

	cin >> n;
	for (i = 0; i < n; i++) {
		cin >> pop;

		while (pop > last_pushed) {
			answer.push_back("+\n");
			st.push(++last_pushed);
		}

		if (st.top() == pop) {
			answer.push_back("-\n");
			st.pop();
		} else {
			cout << "NO";
			return 0;
		}
	}

	n = answer.size();
	for (i = 0; i < n; i++) {
		cout << answer[i];
	}

	return 0;
}