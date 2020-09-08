#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(void) {
	int i, len;
	string S;
	vector<string> dictionary;

	// get a string
	cin >> S;

	// find all suffixes
	len = S.length();
	for (i = 0; i < len; i++) {
		dictionary.push_back(S.substr(i));
	}

	// sort
	sort(dictionary.begin(), dictionary.end());

	// print in alphabetical order
	for (i = 0; i < len; i++) {
		cout << dictionary[i] << '\n';
	}

	return 0;
}