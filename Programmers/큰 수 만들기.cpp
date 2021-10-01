#include <string>

using namespace std;

string solution(string number, int k) {
	int i = 0;
	int size = number.size();

	while (k && i < size - 1) {
		if (number[i] < number[i + 1]) {
			// delete one character
			number.erase(i, 1);
			if (i > 0) i--;
			k--;
		} else {
			i++;
		}
	}

	// if no character deleted, delete the last
	if (k) {
		number.erase(size - k);
	}

	return number;
}
