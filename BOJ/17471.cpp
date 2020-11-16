#include <iostream>
#include <queue>
#include <vector>

#define MAX_POPULATION_GAP 1000
#define min(a, b) (a < b ? a : b)

using namespace std;

struct Area {
	int population;
	int district_id;
	bool is_visited;
	vector<int> adjacent;
};

int get_population_of_district(int start, vector<Area> &areas) {
	int
		district_id,
		n_adjacent,
		population;

	Area
		*now,
		*next;

	queue<Area *>
		visiting_queue;

	now = &areas[start];
	district_id = now->district_id;
	population = 0;

	// start searching
	now->is_visited = true;
	visiting_queue.push(now);
	while (!visiting_queue.empty()) {
		// pop one
		now = visiting_queue.front();
		visiting_queue.pop();

		population += now->population;

		// look for adjacent
		n_adjacent = now->adjacent.size();
		while (n_adjacent--) {
			next = &areas[now->adjacent[n_adjacent]];
			if (!next->is_visited && next->district_id == district_id) {
				next->is_visited = true;
				visiting_queue.push(next);
			}
		}
	}

	return population;
}

int main(void) {
	int
		i, j, // indexers
		N, // the number of area
		n_adjacent,
		bits, max_bits,
		population_1, population_2,
		total_population, population_gap, min_population_gap;

	vector<Area>
		areas;

	// get the number of area
	cin >> N;
	areas.resize(N);

	// get population of each area
	total_population = 0;
	for (i = 0; i < N; i++) {
		cin >> areas[i].population;
		total_population += areas[i].population;
	}

	// set adjacent for each area
	for (i = 0; i < N; i++) {
		cin >> n_adjacent;
		areas[i].adjacent.resize(n_adjacent);
		while (n_adjacent--) {
			cin >> j;
			areas[i].adjacent.push_back(j - 1);
		}
	}

	// use bit-masking
	min_population_gap = MAX_POPULATION_GAP;
	max_bits = 1 << (N - 1);
	for (bits = 1; bits < max_bits; bits++) {

		// init all area
		for (i = 0; i < N; i++) {
			areas[i].district_id = (bits >> i) & 1;
			areas[i].is_visited = false;
		}

		population_1 = get_population_of_district(0, areas);
		for (i = 1; i < N; i++) {
			if (!areas[i].is_visited) {
				population_2 = get_population_of_district(i, areas);
				break;
			}
		}

		// invalid districts
		if (total_population != population_1 + population_2) continue;

		// check population gap
		population_gap = population_1 - population_2;
		if (population_gap < 0)
			population_gap = -population_gap;

		// update minimum gap
		min_population_gap = min(min_population_gap, population_gap);
	}

	// print the answer
	cout << (min_population_gap == MAX_POPULATION_GAP ? -1 : min_population_gap);

	return 0;
}