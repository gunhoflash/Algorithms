/*

1,000,000 의 제곱은 1,000,000,000,000 이고
n은 최대 1,000,000,000,000,000,000 이므로
분명 정답의 주기가 있다.

그 주기는 1500000 이었다.

*/
#include <iostream>

using namespace std;

int main(void) {
	long long n;
	int
		temp,
		n1 = 0, // the fibonacci number
		n2 = 1; // the fibonacci number

	cin >> n;
	n %= 1500000;

	while (--n) {
		temp = n1;
		n1 = n2;
		n2 = (n2 + temp) % 1000000;
	}

	cout << n2;

	return 0;
}

