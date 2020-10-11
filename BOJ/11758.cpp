#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>

using namespace std;

bool on_one_line(int x1, int y1, int x2, int y2, int x3, int y3) {
	int dx1, dx2, dy1, dy2;

	dx1 = x2 - x1;
	dx2 = x3 - x2;
	dy1 = y2 - y1;
	dy2 = y3 - y2;

	if (dx1 == 0 || dx2 == 0 || dy1 == 0 || dy2 == 0) {
		if ((dx1 == 0 && dx2 == 0) || (dy1 == 0 && dy2 == 0)) {
			return true;
		}
		return false;
	}

	return (dy1 * dx2 == dy2 * dx1); // dy1/dx1 == dy2/dx2
}

int main(void) {
	int
		x1, x2, x3,
		y1, y2, y3;

	double
		angle, angle1, angle2;

	// get coordinates
	cin >> x1 >> y1
	    >> x2 >> y2
	    >> x3 >> y3;

	if (on_one_line(x1, y1, x2, y2, x3, y3)) {
		cout << 0;
	} else {
		// get angles
		angle1 = atan2(y2 - y1, x2 - x1);
		angle2 = atan2(y3 - y2, x3 - x2);
		angle = angle2 - angle1;
		if (angle > M_PI) {
			angle -= 2 * M_PI;
		} else if (angle < -M_PI) {
			angle += 2 * M_PI;
		}

		// check angles
		cout << (angle < 0 ? -1 : 1);
	}

	return 0;
}