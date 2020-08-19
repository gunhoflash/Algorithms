#include <iostream>

using namespace std;

int main(void) {
	int N, r, c, answer;

	// get data
	cin >> N >> r >> c;

	// the size of matrix is 2^N
	N = 1 << N;

	// calculate the answer
	answer = 0;
	while (N > 0) {
		N /= 2;
		if (r >= N) {
			answer += N * N * 2;
			r -= N;
		}
		if (c >= N) {
			answer += N * N;
			c -= N;
		}
	}

	// print out the answer
	cout << answer;
	return 0;
}