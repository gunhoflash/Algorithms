#include <iostream>
#include <set>

using namespace std;

int main(void) {
	int N, M;
	set<int> numbers;

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	// init set
	cin >> N;
	while (N--) {
		int num;
		cin >> num;
		numbers.insert(num);
	}

	// get queries
	cin >> M;
	while (M--) {
		int num;
		cin >> num;
		cout << (numbers.find(num) != numbers.end() ? 1 : 0) << '\n';
	}

	return 0;
}
