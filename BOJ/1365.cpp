#include <iostream>
#include <vector>

using namespace std;

int main(void) {
	int N;
	vector<int> last;

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N;
	for (int i = 0; i < N; i++) {
		int n;
		cin >> n;

		vector<int>::iterator it = lower_bound(last.begin(), last.end(), n);

		if (it == last.end()) {
			last.push_back(n);
		} else {
			(*it) = n;
		}
	}

	cout << N - last.size();

	return 0;
}
