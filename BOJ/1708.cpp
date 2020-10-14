#define _USE_MATH_DEFINES

#include <algorithm>
#include <cmath>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

struct Point {
	double angle;
	int x;
	int y;
};

bool cmp_point(Point &p, Point &q) {
	return p.angle < q.angle;
}

bool is_counter_clockwise(Point &a, Point &b, Point &c) {
	return a.x * b.y + b.x * c.y + c.x * a.y - a.y * b.x - b.y * c.x - c.y * a.x > 0;
}

int main(void) {
	int
		i, // indexer
		N, // the number of points
		x, y, // coordinates
		start_x, start_y, start_index;

	vector<Point> points;

	stack<Point> st_points;
	Point p, q;

	cin >> N;
	points.resize(N);

	start_x = -40001;
	start_y =  40001;
	for (i = 0; i < N; i++) {
		cin >> x >> y;
		points[i].x = x;
		points[i].y = y;

		// find bottom point
		if (y < start_y || (y == start_y && x > start_x)) {
			start_x     = x;
			start_y     = y;
			start_index = i;
		}
	}

	// get angles and sort by angle
	for (i = 0; i < N; i++) {
		points[i].angle = atan2(points[i].y - start_y, points[i].x - start_x);
	}
	points[start_index].angle = -1;
	sort(points.begin(), points.end(), cmp_point);
	points.push_back(points[0]);

	// look for all points
	for (i = 0; i < N + 1; i++) {
		while (true) {
			if (st_points.size() < 2) {
				// handle exception: must push
				st_points.push(points[i]);
				break;
			}

			p = st_points.top();
			st_points.pop();
			q = st_points.top();

			if (is_counter_clockwise(q, p, points[i])) {
				// ok
				st_points.push(p);
				st_points.push(points[i]);
				break;
			}
		}
	}

	// print the answer
	cout << st_points.size() - 1;

	return 0;
}