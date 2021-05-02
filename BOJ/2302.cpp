#define MAX 41

#include <iostream>

using namespace std;

int main(void) {
	int
		N,
		M,
		vip_prev, vip_now,
		answer = 1,
		fibo[MAX] = { 0 };

	// config fibonacci list
	fibo[0] = fibo[1] = 1;
	for (int i = 2; i < MAX; i++) {
		fibo[i] = fibo[i - 1] + fibo[i - 2];
	}

	cin >> N >> M;

	// calculate answer
	vip_prev = 0;
	while (M--) {
		cin >> vip_now;
		answer *= fibo[vip_now - vip_prev - 1];
		vip_prev = vip_now;
	}
	answer *= fibo[N - vip_prev];

	cout << answer;

	return 0;
}
