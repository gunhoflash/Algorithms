#include <iostream>
#include <cmath>

using namespace std;

typedef pair<double, double> Point;

double get_triangle_area(Point &p1, Point &p2, Point &p3) {
	return (
		(p1.first * p2.second + p2.first * p3.second + p3.first * p1.second)
		-
		(p2.first * p1.second + p3.first * p2.second + p1.first * p3.second)
	) / (double)2;
}

int main(void) {
	int
		i, // indexer
		N; // the number of points

	double
		area; // the answer

	Point
		p0, // the first point
		p1, p2; // other 2 points

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	// get the number of points
	cin >> N;
	N -= 2;

	// get the initial points
	cin >> p0.first >> p0.second;
	cin >> p1.first >> p1.second;

	// get other points and calculate the total area of all triangles
	area = 0;
	while (N--) {
		cin >> p2.first >> p2.second;
		area += get_triangle_area(p0, p1, p2);
		p1.first  = p2.first;
		p1.second = p2.second;
	}

	if (area < 0)
		area = -area;

	// print the answer
	cout << fixed;
	cout.precision(1);
	cout << area;

	return 0;
}