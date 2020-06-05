#include <vector>

using namespace std;

vector<int> bounds;

int f(vector<int> numbers, int i, int target) {
	int r = 0, n = numbers[i];

	if (i == numbers.size() - 1) {
		if (n == target || -n == target) r = 1;
	} else {
		if (target - n <= bounds[i + 1])
			r += f(numbers, i + 1, target - n);
		if (target + n >= -bounds[i + 1])
			r += f(numbers, i + 1, target + n);
	}

	return r;
}

int solution(vector<int> numbers, int target) {
	int i, sum = 0;

	bounds.resize(numbers.size());
	for (i = numbers.size() - 1; i >= 0; i--) {
		sum += numbers[i];
		bounds[i] = sum;
	}

	return f(numbers, 0, target);
}