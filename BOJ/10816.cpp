#include <iostream>
#include <map>

using namespace std;

int main(void) {
	int N, M;
	map<int, int> deck;

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N;
	while (N--) {
		int n;
		cin >> n;
		deck[n]++;
	}

	cin >> M;
	while (M--) {
		int n;
		cin >> n;
		cout << deck[n] << ' ';
	}

	return 0;
}
