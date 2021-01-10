#include <iostream>

using namespace std;

int main(void) {
	long long N;

	// get the number of stones
	cin >> N;

	// print the winner
	N %= 7;
	cout << (N == 0 || N == 2 ? "CY" : "SK");

	return 0;
}