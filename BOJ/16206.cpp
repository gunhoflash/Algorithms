#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

bool compare_cake(int a, int b) {
	bool ra = a % 10 == 0;
	bool rb = b % 10 == 0;
	if (ra) {
		return rb ? a < b : true;
	} else {
		return false;
	}
}

int main(void) {
	int N, M, n_cake;
	vector<int> cakes;

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N >> M;

	// init cakes
	cakes.resize(N);
	for (int i = 0; i < N; i++) {
		cin >> cakes[i];
	}
	sort(cakes.begin(), cakes.end(), compare_cake);

	// slice cakes
	n_cake = 0;
	for (int cake : cakes) {
		// slice cake
		while (M && cake > 10) {
			cake -= 10;
			n_cake++;
			M--;
		}

		// remained also edible
		if (cake == 10) n_cake++;
	}

	// print the answer
	cout << n_cake;

	return 0;
}
