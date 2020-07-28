#include <iostream>

using namespace std;

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	//x=(c-by)/a=(f-ey)/d, af-aey=dc-dby, y=(af-dc)/(ae-db)
	
	int a, b, c, d, e, f, x, y;

	cin >> a >> b >> c >> d >> e >> f;

	if (a == 0) {
		y = c / b;
		x = (f - e * y) / d;
	}
	else if (b == 0) {
		x = c / a;
		y = (f - d * x) / e;
	}
	else if (d == 0) {
		y = f / e;
		x = (c - b * y) / a;
	}
	else if (e == 0) {
		x = f / d;
		y = (c - a * x) / b;
	}
	else {
		// a, b, d, e is not zero
		y = (a * f - d * c) / (a * e - d * b);
		x = (f - e*y) / d;
	}

	cout << x << ' ' << y;
	return 0;
}