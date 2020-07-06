#include <string>

using namespace std;

string solution(string number, int k) {
	int i, size;

	while (k > 0) {
		size = number.size();
		for (i = 0; i < size - 1; i++) {
			// delete one character
			if (number[i] < number[i + 1]) {
				number.erase(i, 1);
				k--;
				break;
			}
		}

		// if no character deleted, delete the last
		if (i >= size - 1) {
			number.erase(size - k);
			k = 0;
		}
	}

	return number;
}