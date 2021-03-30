#include <iostream>
#include <cmath>

using namespace std;

int gap_to_day(int gap) {
	int day = sqrt(gap);
	if (day == 0)               return 0;
	if (day * day == gap)       return day * 2 - 1;
	if (day * day + day >= gap) return day * 2;
	                            return day * 2 + 1;
}

int main(void) {
	int X, Y;

	cin >> X >> Y;
	cout << gap_to_day(Y - X);

	return 0;
}