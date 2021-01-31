#include <iostream>

using namespace std;

int main(void) {
	int i, N, K, answer;

	cin >> N >> K;

	answer = 1;
	for (i = 0; i < K; i++) answer *= (N - i);
	for (i = 0; i < K; i++) answer /= (i + 1);

	cout << answer;

	return 0;
}