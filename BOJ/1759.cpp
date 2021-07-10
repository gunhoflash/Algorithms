#include <algorithm>
#include <iostream>

using namespace std;

bool is_aeiou(char c) {
	switch (c) {
		case 'a':
		case 'e':
		case 'i':
		case 'o':
		case 'u':
			return true;
		default:
			return false;
	}
}

int get_number_of_1(int bits, int length) {
	int n = 0;
	for (int i = 0; i < length; i++) {
		n += (bits >> i) & 1;
	}
	return n;
}

int main(void) {
	int L, C;
	char c[15];

	cin >> L >> C;

	// get characters and sort
	for (int i = 0; i < C; i++) {
		cin >> c[i];
	}
	sort(c, c + C);

	for (int bits = (1 << C) - 1; bits > 0; bits--) {
		// length not matched
		if (get_number_of_1(bits, C) != L) continue;

		// parse bits to string
		int n_aeiou = 0;
		string code = "";
		for (int i = C - 1; i >= 0; i--) {
			if ((bits >> i) & 1) {
				code += c[C - 1 - i];
				n_aeiou += is_aeiou(c[C - 1 - i]) ? 1 : 0;
			}
		}

		// character not matched
		if (n_aeiou == 0 || n_aeiou > L - 2) continue;

		// print code
		cout << code << '\n';
	}

	return 0;
}
