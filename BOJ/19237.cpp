#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

#define TIMEOUT 1000

#define UP         1
#define DOWN       2
#define LEFT       3
#define RIGHT      4

#define check_smell_area(N, r, c, d, smells, smell, result)                         \
	switch (d) {                                                                    \
		case UP:    result = (r >     0 && smells[r - 1][c].first == smell); break; \
		case DOWN:  result = (r < N - 1 && smells[r + 1][c].first == smell); break; \
		case LEFT:  result = (c >     0 && smells[r][c - 1].first == smell); break; \
		case RIGHT: result = (c < N - 1 && smells[r][c + 1].first == smell); break; \
	}

#define set_position_and_direction(shark, r, c, d) \
	switch (d) {                                   \
		case UP:    r--; break;                    \
		case DOWN:  r++; break;                    \
		case LEFT:  c--; break;                    \
		case RIGHT: c++; break;                    \
	}                                              \
	shark[1] = r, shark[2] = c, shark[3] = d;

#define get_position_and_direction(shark, r, c, d) (r = shark[1], c = shark[2], d = shark[3])
#define is_same_position(shark1, shark2) (shark1[1] == shark2[1] && shark1[2] == shark2[2])

int main(void) {
	int
	N,          // 2 ~ 20
	M,          // 2 ~ N^2
	k,          // 1 ~ 1000
	i, j,       // indexers
	n, r, c, d, // number, row, column, and direction of the shark
	size,       // size of vector
	t;          // temp or time

	bool result;

	vector<vector<pair<int, int>>> smells; // [[{number, time}, ...], ...]
	vector<vector<int>> sharks;            // [[number, row, column, direction, ...priorities by direction], ...]
	vector<int> shark;

	// init N, M, and k
	cin >> N >> M >> k;

	// init smells
	for (i = 0; i < N; i++) {
		smells.push_back(vector<pair<int, int>>(N, make_pair(0, 0)));
	}

	// get the sharks
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			cin >> t;
			if (t == 0) continue;

			sharks.push_back({ t, i, j, UP });
			smells[i][j].first = t;
			smells[i][j].second = k;
		}
	}

	// sort sharks by number
	sort(sharks.begin(), sharks.end());

	// set direction of each shark
	size = sharks.size();
	for (i = 0; i < size; i++) {
		cin >> sharks[i][3];
	}

	// get priorities by direction
	for (i = 0; i < size; i++) {
		for (j = 0; j < 16; j++) {
			cin >> t;
			sharks[i].push_back(t);
		}
	}

	// for every time,
	t = 0;
	while (t <= TIMEOUT) {
		size = sharks.size();
		if (size == 1) break;

		// move every shark from 1 to the last
		for (i = 0; i < size; i++) {
			shark = sharks[i];
			get_position_and_direction(shark, r, c, d);
			d *= 4;
			result = false;

			// find non-smell area by priority order
			for (j = 0; j < 4; j++) {
				check_smell_area(N, r, c, shark[d + j], smells, 0, result)
				if (result) break;
			}
			// if the area not found, find my-smell area by priority order
			if (!result) {
				for (j = 0; j < 4; j++) {
					check_smell_area(N, r, c, shark[d + j], smells, shark[0], result)
					if (result) break;
				}
			}

			// move
			// update position and direction
			set_position_and_direction(shark, r, c, shark[d + j])

			// if other stronger shark exist, delete the shark
			for (j = 0; j < i; j++) {
				if (is_same_position(shark, sharks[j])) {
					sharks.erase(sharks.begin() + i);
					size--;
					i--;
					j = -1;
					break;
				}
			}

			// if not, update real data
			if (j != -1) {
				sharks[i][1] = shark[1];
				sharks[i][2] = shark[2];
				sharks[i][3] = shark[3];
			}
		}

		// down smells
		for (i = 0; i < N; i++) {
			for (j = 0; j < N; j++) {
				if (smells[i][j].first != 0) {
					if (smells[i][j].second == 1) {
						smells[i][j].first = 0;
					} else {
						smells[i][j].second--;
					}
				}
			}
		}

		// make smells
		for (i = 0; i < size; i++) {
			r = sharks[i][1];
			c = sharks[i][2];
			smells[r][c].first = sharks[i][0];
			smells[r][c].second = k;
		}

		t++;
	}

	// print the answer
	if (t > TIMEOUT) t = -1;
	cout << t;

	return 0;
}