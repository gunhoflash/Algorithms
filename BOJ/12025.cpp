#include <iostream>
#include <string>

using namespace std;

int main(void) {
	int
		i, // indexer
		len; // length of the password

	string
		password;

	long long
		k;

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	// get the changed password
	cin >> password;
	len = password.length();

	// revert the original password
	cin >> k;
	k--;

	for (i = len - 1; i >= 0; i--) {
		switch (password[i]) {
			case '1':
			case '6':
				password[i] = (k & 1 ? '6' : '1');
				k >>= 1;
				break;

			case '2':
			case '7':
				password[i] = (k & 1 ? '7' : '2');
				k >>= 1;
				break;
		}
	}

	// if {k} is valid, print the original password
	cout << (k ? "-1" : password);

	return 0;
}