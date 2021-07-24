#include <iostream>
#include <string>
#include <vector>

using namespace std;

string reverse(const string &s) {
	string r;
	int i = s.size();
	while (i--) r += s[i];
	return r;
}

// return whether T is able to be shorten as S
bool can_reduce(const string &T, const string &S) {
	int size_T = T.size(), size_S = S.size();
	int n_operations = size_T - size_S;
	int first = 0, last = size_T - 1;
	bool is_reversed = false;

	// shorten T
	while (n_operations--) {
		if (is_reversed) {
			if (T[first] == 'B') {
				is_reversed = false;
			}
			first++;
		} else {
			if (T[last] == 'B') {
				is_reversed = true;
			}
			last--;
		}
	}

	return S == (
		is_reversed
		? reverse(T.substr(first, size_S))
		: T.substr(first, size_S)
	);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	string S, T;
	cin >> S >> T;
	cout << (can_reduce(T, S) ? '1' : '0');

	return 0;
}
