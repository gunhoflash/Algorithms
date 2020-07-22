#include <iostream>
#include <vector>

using namespace std;

typedef vector<vector<int>> Fishes;

void copy_fishes(Fishes from, Fishes &fishes) {
	int i;
	for (i = 0; i < 17; i++) {
		fishes.push_back({
			from[i][0],
			from[i][1],
			from[i][2],
			from[i][3]
		});
	}
}

void copy_fish_map(int from[4][4], int (&fish_map)[4][4]) {
	int i, j;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			fish_map[i][j] = from[i][j];
		}
	}
}

int get_eats(Fishes fishes, int fish_map[4][4]) {
	int i, j, r, c, tr, tc, eats, eats_temp;
	bool movable;

	Fishes fishes_copied;
	int fish_map_copied[4][4];

	// move fishes
	for (i = 1; i < 17; i++) {
		if (fishes[i][0] == 0) continue; // dead fish
		/*
			direction
				1: up
				3: left
				5: down
				7: right
		*/
		r = fishes[i][1];
		c = fishes[i][2];
		movable = false;
		while (true) {
			switch (fishes[i][3]) {
				case 1:
					if (r > 0 && fish_map[r - 1][c] >= 0) {
						tr = r - 1;
						tc = c;
						movable = true;
					}
					break;
				case 2:
					if (r > 0 && c > 0 && fish_map[r - 1][c - 1] >= 0) {
						tr = r - 1;
						tc = c - 1;
						movable = true;
					}
					break;
				case 3:
					if (c > 0 && fish_map[r][c - 1] >= 0) {
						tr = r;
						tc = c - 1;
						movable = true;
					}
					break;
				case 4:
					if (r < 3 && c > 0 && fish_map[r + 1][c - 1] >= 0) {
						tr = r + 1;
						tc = c - 1;
						movable = true;
					}
					break;
				case 5:
					if (r < 3 && fish_map[r + 1][c] >= 0) {
						tr = r + 1;
						tc = c;
						movable = true;
					}
					break;
				case 6:
					if (r < 3 && c < 3 && fish_map[r + 1][c + 1] >= 0) {
						tr = r + 1;
						tc = c + 1;
						movable = true;
					}
					break;
				case 7:
					if (c < 3 && fish_map[r][c + 1] >= 0) {
						tr = r;
						tc = c + 1;
						movable = true;
					}
					break;
				case 8:
					if (r > 0 && c < 3 && fish_map[r - 1][c + 1] >= 0) {
						tr = r - 1;
						tc = c + 1;
						movable = true;
					}
					break;
			}

			if (movable) break;
			fishes[i][3] = (fishes[i][3] % 8) + 1;
		}

		// switch position
		j = fish_map[tr][tc];
		fish_map[r][c] = j;
		fish_map[tr][tc] = i;
		fishes[i][1] = tr;
		fishes[i][2] = tc;
		if (j != 0) {
			// switch with a fish, no empty area
			fishes[j][1] = r;
			fishes[j][2] = c;
		}
	}

	// get position of the shark
	r = fishes[0][1];
	c = fishes[0][2];

	// get direction of the shark
	switch (fishes[0][3]) {
		case 1: tr = -1; tc =  0; break;
		case 2: tr = -1; tc = -1; break;
		case 3: tr =  0; tc = -1; break;
		case 4: tr =  1; tc = -1; break;
		case 5: tr =  1; tc =  0; break;
		case 6: tr =  1; tc =  1; break;
		case 7: tr =  0; tc =  1; break;
		case 8: tr = -1; tc =  1; break;
	}

	eats = 0;
	fish_map[r][c] = 0;
	while (true) {
		// move the shark
		r += tr;
		c += tc;

		// out of the map
		if (r < 0 || r > 3 || c < 0 || c > 3) break;

		// no fish area
		if (fish_map[r][c] == 0) continue;

		// eat fish
		i = fish_map[r][c];
		// copy all values
		copy_fishes(fishes, fishes_copied);
		copy_fish_map(fish_map, fish_map_copied);
		// set position and direction of the shark
		fishes_copied[0][1] = r;
		fishes_copied[0][2] = c;
		fishes_copied[0][3] = fishes_copied[i][3];
		fish_map_copied[r][c] = -1;
		// fish dead
		fishes_copied[i][0] = 0;
		// recursively calculate
		eats_temp = i + get_eats(fishes_copied, fish_map_copied);
		if (eats_temp > eats) eats = eats_temp;

		// prevent memory leak
		j = fishes_copied.size();
		for (i = 0; i < j; i++)
			fishes_copied[i].clear();
		fishes_copied.clear();
	}

	return eats;
}

int main(void) {
	/*
		order by number
		[ is_live, row, column, direction ]
	*/
	Fishes fishes(17, vector<int>()); // index 0 is for the shark
	int fish_map[4][4]; // 0: no fish, -1: shark

	int i, j, number, direction, answer;

	// get fish data
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			cin >> number >> direction;
			fish_map[i][j] = number;
			fishes[number] = { 1, i, j, direction };
		}
	}

	// init shark and eat fish at (0, 0)
	fishes[0] = { 0, 0, 0, 0 };

	i = fish_map[0][0];
	fishes[i][0] = 0; // fish dead
	fishes[0][3] = fishes[i][3]; // init direction of the shark
	fish_map[0][0] = -1; // place the shark

	answer = i + get_eats(fishes, fish_map);
	cout << answer;

	return 0;
}