#define MAX_ROUTE_LENGTH 10000
#define WALL 0
#define WAY 1

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Plate {
	int tile[5][5]; // 1: way, 0: wall
	int is_visited[5][5]; // -1: not visited, (else): visited
};

struct Point {
	int ip; // index of a plate
	int r; // row
	int c; // column
	int distance; // distance from the start
};

// rotate a plate clockwise
void rotate_plate(Plate *plate) {
	int temp[4] = {
		plate->tile[0][0],
		plate->tile[0][1],
		plate->tile[0][2],
		plate->tile[0][3]
	};

	plate->tile[0][3] = plate->tile[1][0];
	plate->tile[0][2] = plate->tile[2][0];
	plate->tile[0][1] = plate->tile[3][0];
	plate->tile[0][0] = plate->tile[4][0];
	plate->tile[1][0] = plate->tile[4][1];
	plate->tile[2][0] = plate->tile[4][2];
	plate->tile[3][0] = plate->tile[4][3];
	plate->tile[4][0] = plate->tile[4][4];
	plate->tile[4][1] = plate->tile[3][4];
	plate->tile[4][2] = plate->tile[2][4];
	plate->tile[4][3] = plate->tile[1][4];
	plate->tile[4][4] = plate->tile[0][4];
	plate->tile[3][4] = temp[3];
	plate->tile[2][4] = temp[2];
	plate->tile[1][4] = temp[1];
	plate->tile[0][4] = temp[0];

	temp[0] = plate->tile[1][1];
	temp[1] = plate->tile[1][2];

	plate->tile[1][2] = plate->tile[2][1];
	plate->tile[1][1] = plate->tile[3][1];
	plate->tile[2][1] = plate->tile[3][2];
	plate->tile[3][1] = plate->tile[3][3];
	plate->tile[3][2] = plate->tile[2][3];
	plate->tile[3][3] = plate->tile[1][3];
	plate->tile[2][3] = temp[1];
	plate->tile[1][3] = temp[0];
}

// set all values of {plate.is_visited} as false
void init_visited_plate(Plate *plate) {
	int i, j;
	for (i = 0; i < 5; i++) {
		for (j = 0; j < 5; j++) {
			plate->is_visited[i][j] = false;
		}
	}
}

int find_route_length(Plate *p_plates[5], int min_route_length) {
	int
		i,
		ip, // index of a plate
		r, // row
		c, // column
		distance; // distance from the start

	Point
		now;

	queue<Point>
		visiting_queue;

	// init all {is_visited}
	for (i = 0; i < 5; i++) {
		init_visited_plate(p_plates[i]);
	}

	// start from { 0, 0, 0 }
	if (p_plates[0]->tile[0][0] == WAY) {
		visiting_queue.push({ 0, 0, 0, 0 });
	}

	while (!visiting_queue.empty()) {
		// pop one
		now      = visiting_queue.front();
		ip       = now.ip;
		r        = now.r;
		c        = now.c;
		distance = now.distance;
		visiting_queue.pop();

		if (distance == min_route_length) {
			// early stop
			break;
		} else if (ip == 4 && r == 4 && c == 4) {
			// destination found
			min_route_length = distance;
			break;
		}

		// search adjacent
		distance++;
		if (ip > 0 && p_plates[ip - 1]->tile[r][c] == WAY && !p_plates[ip - 1]->is_visited[r][c]) {
			p_plates[ip - 1]->is_visited[r][c] = true;
			visiting_queue.push({ ip - 1, r, c, distance });
		}
		if (ip < 4 && p_plates[ip + 1]->tile[r][c] == WAY && !p_plates[ip + 1]->is_visited[r][c]) {
			p_plates[ip + 1]->is_visited[r][c] = true;
			visiting_queue.push({ ip + 1, r, c, distance });
		}
		if (r > 0 && p_plates[ip]->tile[r - 1][c] == WAY && !p_plates[ip]->is_visited[r - 1][c]) {
			p_plates[ip]->is_visited[r - 1][c] = true;
			visiting_queue.push({ ip, r - 1, c, distance });
		}
		if (r < 4 && p_plates[ip]->tile[r + 1][c] == WAY && !p_plates[ip]->is_visited[r + 1][c]) {
			p_plates[ip]->is_visited[r + 1][c] = true;
			visiting_queue.push({ ip, r + 1, c, distance });
		}
		if (c > 0 && p_plates[ip]->tile[r][c - 1] == WAY && !p_plates[ip]->is_visited[r][c - 1]) {
			p_plates[ip]->is_visited[r][c - 1] = true;
			visiting_queue.push({ ip, r, c - 1, distance });
		}
		if (c < 4 && p_plates[ip]->tile[r][c + 1] == WAY && !p_plates[ip]->is_visited[r][c + 1]) {
			p_plates[ip]->is_visited[r][c + 1] = true;
			visiting_queue.push({ ip, r, c + 1, distance });
		}
	}

	// clear queue
	while (!visiting_queue.empty()) visiting_queue.pop();

	return min_route_length;
}

int find_min_route_length(Plate plates[5]) {
	int
		io1, io2, io3, io4, io5, // indexers for order of plates
		ir1, ir2, ir3, ir4, ir5, // indexers for rotation of plates
		route_length, min_route_length; // length of a route

	bool
		is_reserved[5];

	Plate
		*p_plates[5];

	min_route_length = MAX_ROUTE_LENGTH;

	// init {is_reserved}
	for (io1 = 0; io1 < 5; io1++) {
		is_reserved[io1] = false;
	}

	// select the order of plates
	for (io1 = 0; io1 < 5; io1++) {
		is_reserved[io1] = true;
		p_plates[0] = plates + io1;
		for (io2 = 0; io2 < 5; io2++) {
			if (is_reserved[io2]) continue;
			is_reserved[io2] = true;
			p_plates[1] = plates + io2;
			for (io3 = 0; io3 < 5; io3++) {
				if (is_reserved[io3]) continue;
				is_reserved[io3] = true;
				p_plates[2] = plates + io3;
				for (io4 = 0; io4 < 5; io4++) {
					if (is_reserved[io4]) continue;
					is_reserved[io4] = true;
					p_plates[3] = plates + io4;
					for (io5 = 0; io5 < 5; io5++) {
						if (is_reserved[io5]) continue;
						p_plates[4] = plates + io5;

						// select the rotation of plates
						for (ir1 = 0; ir1 < 4; ir1++) {
							for (ir2 = 0; ir2 < 4; ir2++) {
								for (ir3 = 0; ir3 < 4; ir3++) {
									for (ir4 = 0; ir4 < 4; ir4++) {
										for (ir5 = 0; ir5 < 4; ir5++) {

											// search route
											route_length = find_route_length(p_plates, min_route_length);
											min_route_length = (min_route_length > route_length) ? route_length : min_route_length;

											// early stop
											if (min_route_length == 12)
												return 12;

											rotate_plate(p_plates[4]);
										}
										rotate_plate(p_plates[3]);
									}
									rotate_plate(p_plates[2]);
								}
								rotate_plate(p_plates[1]);
							}
							rotate_plate(p_plates[0]);
						}

					}
					is_reserved[io4] = false;
				}
				is_reserved[io3] = false;
			}
			is_reserved[io2] = false;
		}
		is_reserved[io1] = false;
	}

	// handle exception: no route found
	if (min_route_length == MAX_ROUTE_LENGTH) {
		min_route_length = -1;
	}

	return min_route_length;
}

int main(void) {
	int
		i, j, k; // indexers

	Plate plates[5];

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	// get all data
	for (i = 0; i < 5; i++) {
		// get data for a plate
		for (j = 0; j < 5; j++) {
			for (k = 0; k < 5; k++) {
				cin >> plates[i].tile[j][k];
			}
		}
	}

	cout << find_min_route_length(plates);

	return 0;
}