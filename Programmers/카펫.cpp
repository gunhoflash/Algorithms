#include <vector>

using namespace std;

vector<int> solution(int brown, int yellow) {
	int i;

	brown = (brown - 4) / 2;
	for (i = 1; i < yellow; i++) {
		if (yellow % i == 0) {
			if (brown - i == yellow / i) {
				return { brown - i + 2, i + 2 };
			}
		}
	}
}