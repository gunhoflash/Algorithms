#include <iostream>
#include <vector>

using namespace std;

int main(void) {
	int N;
	vector<int> last;

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N;
	while (N--) {
		int n;
		cin >> n;

		vector<int>::iterator it = lower_bound(last.begin(), last.end(), n);

		if (it == last.end()) {
			last.push_back(n);
		} else {
			(*it) = n;
		}
	}

	cout << last.size();

	return 0;
}
