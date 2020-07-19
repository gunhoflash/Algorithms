#include <iostream>

using namespace std;

int main(void) {
	int number, n1, n2, n3, n4, n5;

	while (true) {
		cin >> number;

		if (number == 0) break;

		n1 = number / 10000;
		n2 = (number % 10000) / 1000;
		n3 = (number % 1000) / 100;
		n4 = (number % 100) / 10;
		n5 = number % 10;

		if (number < 10) {
			cout << "yes" << endl;
		} else if (number < 100) {
			if (number % 11 == 0) {
				cout << "yes" << endl;
			} else {
				cout << "no" << endl;
			}
		} else if (number < 1000) {
			if (n3 == n5) {
				cout << "yes" << endl;
			} else {
				cout << "no" << endl;
			}
		} else if (number < 10000) {
			if (n2 == n5 && n3 == n4) {
				cout << "yes" << endl;
			} else {
				cout << "no" << endl;
			}
		} else {
			if (n1 == n5 && n2 == n4) {
				cout << "yes" << endl;
			} else {
				cout << "no" << endl;
			}
		}
	}

	return 0;
}