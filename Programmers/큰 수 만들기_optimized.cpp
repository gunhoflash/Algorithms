#include <string>

using namespace std;

string solution(string number, int k) {
	int i, size;

	size = number.size();
	for (i = 0; i < size - 1; i++) {
		// delete one character
		if (number[i] < number[i + 1]) {
			number.erase(i, 1);
			if (--k == 0) break;
			if (i > 0) i -= 2;
			else i--;
		}
	}

	// if no character deleted, delete the last
	if (k > 0) {
		number.erase(size - k);
	}

	return number;
}