#include <iostream>

using namespace std;

enum PALINDROME_STATUS {
	palindrome = 0,
	pseudo_palindrome = 1,
	nothing = 2
};

PALINDROME_STATUS get_palindrome_status(string str, int i, int j, bool pseudo_acceptable) {
	PALINDROME_STATUS palindrome_status = palindrome;

	while (i <= j) {
		if (str[i] == str[j]) {
			i++;
			j--;
			continue;
		}

		if (!pseudo_acceptable) {
			palindrome_status = nothing;
			break;
		}

		// try to skip i
		if (str[i + 1] == str[j]) {
			PALINDROME_STATUS pseudo_palindrome_status = get_palindrome_status(str, i + 1, j, false);
			if (pseudo_palindrome_status == palindrome) {
				palindrome_status = pseudo_palindrome;
				break;
			}
		}

		// try to skip j
		if (str[i] == str[j - 1]) {
			PALINDROME_STATUS pseudo_palindrome_status = get_palindrome_status(str, i, j - 1, false);
			if (pseudo_palindrome_status == palindrome) {
				palindrome_status = pseudo_palindrome;
				break;
			}
		}

		// nothing
		palindrome_status = nothing;
		break;
	}

	return palindrome_status;
}

void test() {
	string str;
	cin >> str;

	PALINDROME_STATUS palindrome_status = get_palindrome_status(str, 0, str.length() - 1, true);
	cout << palindrome_status << '\n';
}

int main(void) {
	int T;

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> T;
	while (T--) test();

	return 0;
}
